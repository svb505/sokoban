#include "moving.h"
#include "vec2.h"
#include "objects.h"
#include <algorithm>
#include <vector>

Vec2 getDirectionOffset(Direction dir, float speed) {
    switch (dir) {
    case Direction::Up:
        return { 0.0f, speed };

    case Direction::Down:
        return { 0.0f, -speed };

    case Direction::Left:
        return { -speed, 0.0f };

    case Direction::Right:
        return { speed, 0.0f };
    }

    return { 0.0f, 0.0f };
}
bool circleBoxCollision(const Circle& c, const BoxCollider& b) {
    float closestX = std::clamp(
        c.pos.x,
        b.pos.x - b.halfSize,
        b.pos.x + b.halfSize
    );

    float closestY = std::clamp(
        c.pos.y,
        b.pos.y - b.halfSize,
        b.pos.y + b.halfSize
    );

    float dx = c.pos.x - closestX;
    float dy = c.pos.y - closestY;

    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}
bool checkCircleWallCollision(const Circle& player,const Wall& wall) {
    // Вертикальная стена
    if (wall.start.x == wall.end.x) {

        float wallX = wall.start.x;

        float minY = std::min(wall.start.y, wall.end.y);
        float maxY = std::max(wall.start.y, wall.end.y);

        if (player.pos.y + player.radius >= minY && player.pos.y - player.radius <= maxY)
        {
            if (std::abs(player.pos.x - wallX) <= player.radius) return true;
        }
    }

    // Горизонтальная стена
    if (wall.start.y == wall.end.y) {

        float wallY = wall.start.y;

        float minX = std::min(wall.start.x, wall.end.x);
        float maxX = std::max(wall.start.x, wall.end.x);

        if (player.pos.x + player.radius >= minX && player.pos.x - player.radius <= maxX){
            if (std::abs(player.pos.y - wallY) <= player.radius) return true;
        }
    }

    return false;
}
bool checkBoxWallCollision(const BoxCollider& box, const Wall& wall) {
    // Вертикальная стена
    if (wall.start.x == wall.end.x) {

        float wallX = wall.start.x;

        float minY = std::min(wall.start.y, wall.end.y);
        float maxY = std::max(wall.start.y, wall.end.y);

        if (box.pos.y + box.halfSize >= minY && box.pos.y - box.halfSize <= maxY){
            if (std::abs(box.pos.x - wallX) <= box.halfSize) return true;
        }
    }

    // Горизонтальная стена
    if (wall.start.y == wall.end.y) {

        float wallY = wall.start.y;

        float minX = std::min(wall.start.x, wall.end.x);
        float maxX = std::max(wall.start.x, wall.end.x);

        if (box.pos.x + box.halfSize >= minX && box.pos.x - box.halfSize <= maxX){
            if (std::abs(box.pos.y - wallY) <= box.halfSize) return true;
        }
    }

    return false;
}
bool canMoveCircle(const Circle& player,const std::vector<Wall>& walls) {
    for (const Wall& wall : walls) {
        if (checkCircleWallCollision(player, wall)) {
            return false;
        }
    }

    return true;
}
bool canMoveBox(const BoxCollider& box,const std::vector<Wall>& walls) {
    for (const Wall& wall : walls) {

        if (checkBoxWallCollision(box, wall)) {
            return false;
        }
    }

    return true;
}
void tryMovePlayer(Circle& player,std::map<int, BoxCollider>& boxes,const std::vector<Wall>& walls,
    const std::vector<Wall>& wallsPerimetr,std::map<int, bool>& boxDown, Direction dir,float speed){
    Vec2 offset = getDirectionOffset(dir, speed);

    Circle nextPlayer = player;
    nextPlayer.pos.x += offset.x;
    nextPlayer.pos.y += offset.y;

    std::map<int, BoxCollider> nextBoxes = boxes;

    if (!canMoveCircle(nextPlayer, walls) || !canMoveCircle(nextPlayer, wallsPerimetr))
        return;

    std::vector<int> affected;

    for (auto& [id, box] : nextBoxes){
        if (circleBoxCollision(nextPlayer, box)) affected.push_back(id);
    }

    for (int id : affected){
        BoxCollider& box = nextBoxes[id];

        if (boxDown[id]) return;

        BoxCollider movedBox = box;
        movedBox.pos.x += offset.x;
        movedBox.pos.y += offset.y;

        if (!canMoveBox(movedBox, walls) || !canMoveBox(movedBox, wallsPerimetr)) return;

        box = movedBox;
    }

    for (const auto& [id, box] : nextBoxes){
        if (boxDown.at(id)) continue;

        if (std::find(affected.begin(),affected.end(),id) != affected.end()) continue;

        if (circleBoxCollision(nextPlayer, box)) return;
    }

    player = nextPlayer;
    boxes = std::move(nextBoxes);
}