#include "Object/TerrainObject.h"
#include "Manager/JsonManager.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"

TerrainObject::~TerrainObject()
{
}

void TerrainObject::Initialize()
{
    transform->position = Vector2();
	tileInfo = g_JsonManager.GetIntagerData(L"./Resource/Map/StageTest.json", std::vector<std::wstring>{ L"layers", L"data"});
    tileSet = Gdiplus::Image::FromFile(L"./Resource/Tile/Terrain (16x16).png");

    mapGridXCount = g_JsonManager.GetIntagerData(L"./Resource/Map/StageTest.json", { L"width"})[0];
    mapGridYCount = g_JsonManager.GetIntagerData(L"./Resource/Map/StageTest.json", { L"height" })[0];
    tileSize = g_JsonManager.GetIntagerData(L"./Resource/Map/StageTest.json", { L"tileheight" })[0];

    tileGridXCount = tileSet->GetWidth() / tileSize;
    tileGridYCount = tileSet->GetHeight() / tileSize;

    tilemapBitmap = CreateTilemapBitMap(mapGridYCount, mapGridXCount, tileInfo, tileSet);
}

void TerrainObject::UpdateImpl()
{
}

void TerrainObject::RenderImpl()
{
    if (tilemapBitmap == nullptr) return;

    // 목적지: 화면 전체
    Gdiplus::Rect destRect(0, 0, g_WindowConfig.windowWidth, g_WindowConfig.windowHeight);

    // 원본 비트맵에서 복사할 부분
    Gdiplus::Rect srcRect(0, 0, g_WindowConfig.windowWidth, g_WindowConfig.windowHeight);

    graphics->DrawImage(tilemapBitmap,
        destRect,               // 화면에 그릴 위치
        srcRect.X, srcRect.Y,   // 원본에서 시작 위치
        srcRect.Width, srcRect.Height, // 원본 크기
        Gdiplus::UnitPixel);
}

void TerrainObject::SetupTransform(int gridX, int gridY)
{

}

void TerrainObject::OnColliderEnterImpl(GameObject* other)
{
}

void TerrainObject::OnColliderExitImpl(GameObject* other)
{
}

Gdiplus::Bitmap* TerrainObject::CreateTilemapBitMap(int rows, int cols, std::vector<int> tileData, Gdiplus::Image* tileset)
{
    // 타일맵 비트맵 생성
    Gdiplus::Bitmap* tilemapBitmap = new Gdiplus::Bitmap(cols * tileSize, rows * tileSize, PixelFormat32bppARGB);
    Gdiplus::Graphics* gMap = Gdiplus::Graphics::FromImage(tilemapBitmap);
    gMap->Clear(Gdiplus::Color(0, 0, 0, 0)); // 완전 투명하게 클리어

    // 각 타일을 비트맵에 그리기
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            int tile = tileData[y * mapGridXCount + x];  // 타일 ID (0이면 빈 타일)
            if (tile == 0) // 빈 타일
            {

            }
            else
            {
                // 타일 이미지 그리기 (타일셋에서 해당 타일을 찾아서)
                int tileX = (tile - 1) % tileGridXCount;  // 타일셋에서 X 위치
                int tileY = (tile - 1) / tileGridXCount;  // 타일셋에서 Y 위치

                Gdiplus::Rect srcRect(tileX * tileSize, tileY * tileSize, tileSize, tileSize);
                Gdiplus::Rect destRect(x * tileSize, y * tileSize, srcRect.Width, srcRect.Height); // 화면에 그릴 영역
                gMap->DrawImage(tileSet,
                    destRect, srcRect.X, srcRect.Y,
                    srcRect.Width, srcRect.Height,
                    Gdiplus::UnitPixel);

            }
        }
    }

    return tilemapBitmap;


}
