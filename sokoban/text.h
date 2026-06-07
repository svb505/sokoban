#pragma once
#include <string>
#include <vector>

extern bool showText;


void BuildFont();
void PrintText(const char* text);
void drawText(float x, float y, const std::string& text);
void RenderTextHUD(float x, float y, float r, float g, float b, const char* text, int screenW, int screenH);
void RenderTextWorld(float x, float y, float z, float r, float g, float b, const char* text);