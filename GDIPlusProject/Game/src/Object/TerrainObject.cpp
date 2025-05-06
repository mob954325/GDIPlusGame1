#include "Object/TerrainObject.h"
#include "GDIEngineLib/inc/Utility/WindowConfig.h"
#include "Manager/JsonManager.h"
#include "Object/GroundObject.h"
#include "Object/Item/Apple.h"
#include <queue>

TerrainObject::~TerrainObject()
{
    delete tileSet;
    delete tilemapBitmap;
    delete backgroundBitmap;
}

void TerrainObject::Initialize()
{
    transform->position = Vector2();
	tileInfo = g_JsonManager.GetIntagerData(L"./Resource/Map/Stage1.json", std::vector<std::wstring>{ L"layers", L"data"});
    tileSet = Gdiplus::Image::FromFile(L"./Resource/Tile/Terrain (16x16).png");

    mapGridXCount = g_JsonManager.GetIntagerData(L"./Resource/Map/Stage1.json", { L"width"})[0];
    mapGridYCount = g_JsonManager.GetIntagerData(L"./Resource/Map/Stage1.json", { L"height" })[0];
    tileSize = g_JsonManager.GetIntagerData(L"./Resource/Map/Stage1.json", { L"tileheight" })[0];

    tileGridXCount = tileSet->GetWidth() / tileSize;
    tileGridYCount = tileSet->GetHeight() / tileSize;

    tilemapBitmap = CreateTilemapBitMap(mapGridYCount, mapGridXCount, tileInfo, tileSet);
    SetGroundCollider(mapGridYCount, mapGridXCount, tileInfo);

    backgroundBitmap = CreateBackgroundBitmap(mapGridYCount, mapGridXCount);
    objectList = CreateObjects(mapGridYCount, mapGridXCount, tileInfo);
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

    // 배경
    graphics->DrawImage(backgroundBitmap,
        destRect,             
        srcRect.X, srcRect.Y,  
        srcRect.Width, srcRect.Height, 
        Gdiplus::UnitPixel);
    
    // 지형
    graphics->DrawImage(tilemapBitmap,
        destRect,               // 화면에 그릴 위치
        srcRect.X, srcRect.Y,   // 원본에서 시작 위치
        srcRect.Width, srcRect.Height, // 원본 크기
        Gdiplus::UnitPixel);

    for (auto g : groundList)
    {
        Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0), 2.0f); // 빨간색, 두께 1
        Collider* collider = g->GetComponent<Collider>();
        graphics->DrawRectangle(
            &pen,
            (INT)(collider->bound.left),
            (INT)(collider->bound.bottom),
            (INT)(collider->bound.right - collider->bound.left),
            (INT)(collider->bound.top - collider->bound.bottom)
        );
    }
}

Gdiplus::Bitmap* TerrainObject::CreateTilemapBitMap(int rows, int cols, std::vector<int> tileData, Gdiplus::Image* tileset)
{
    // 타일맵 비트맵 생성
    Gdiplus::Bitmap* tilemapBitmap = new Gdiplus::Bitmap(cols * tileSize, rows * tileSize, PixelFormat32bppARGB);
    Gdiplus::Graphics* gMap = Gdiplus::Graphics::FromImage(tilemapBitmap);
    gMap->Clear(Gdiplus::Color(0, 0, 0, 0)); // 완전 투명하게 클리어

    // 각 타일을 비트맵에 그리기
    for (int y = 0; y < rows; ++y) 
    {
        for (int x = 0; x < cols; ++x) 
        {
            int tile = tileData[y * mapGridXCount + x];  // 타일 ID (0이면 빈 타일)
            if (tile == 0 || tile == 241 || tile == 255) continue;// 빈 타일 or 특수 타일
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

    return tilemapBitmap;
}

void TerrainObject::SetGroundCollider(int rows, int cols, std::vector<int> tileData)
{
    int colliderCount = 0;

    // 상하좌우
    int dx[2] = { 1, 0 };
    int dy[2] = { 0, 1 };

    std::vector<bool> visited(rows * cols, false); // 한 줄로 끝

    //for (int i = 0; i < visited.capacity(); i++)
    //{
    //    visited.push_back(false);
    //}

    std::queue<int> q;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            int countX = 0;
            int countY = 0;

            if (visited[y * mapGridXCount + x]) continue;

            int currTileData = tileData[y * mapGridXCount + x];
            if (currTileData == 0 || currTileData == 241 || currTileData == 255) // 특정 타일 무시, 0 무시
            {
                if (currTileData == 255)
                {
                    spawnPosition = Vector2(x * tileSize, y * tileSize);
                }

                visited[y * mapGridXCount + x] = true;
                continue;
            }

            countX = 1;
            countY = 1;

            q.push(y * mapGridXCount + x);
            while (!q.empty())
            {
                int index = q.front();
                int currentX = index % mapGridXCount;
                int currentY = index / mapGridXCount;

                q.pop();
                visited[index] = true;

                for (int i = 0; i < 2; i++)
                {
                    int nextX = currentX + dx[i];
                    int nextY = currentY + dy[i];

                    if (nextX < 0 || nextX >= mapGridXCount || nextY < 0 || nextY >= mapGridYCount) continue; // 범위체크

                    int currTileData = tileData[nextY * mapGridXCount + nextX];
                    if (currTileData == 0 || currTileData == 241) continue; // 특정 타일 무시, 0 무시

                    q.push(nextY * mapGridXCount + nextX);

                    // 개수 갱신
                    if (countX < currentX - x + 1) countX = currentX - x + 1;
                    if (countY < currentY - y + 1) countY = currentY - y + 1;
                }
            } // while

            GroundObject* ground = new GroundObject();
            ground->SetupTransform(tileSize, x, y, countX, countY); // 시작한 위치로부터 카운트 변수만큼 collider 생성
            groundList.push_back(ground);
            printf("count : %d, x: %d y: %d\n", ++colliderCount, countX, countY);

        } // for x
    } // for y
}

Gdiplus::Bitmap* TerrainObject::CreateBackgroundBitmap(int rows, int cols)
{
    // 타일맵 비트맵 생성
    int backgroundTileSize = 32;
    Gdiplus::Image* backgroundTile = Gdiplus::Image::FromFile(L"./Resource/Tile/Blue.png");
    Gdiplus::Bitmap* backgroundBitmap = new Gdiplus::Bitmap(cols * backgroundTileSize, rows * backgroundTileSize, PixelFormat32bppARGB);
    Gdiplus::Graphics* gMap = Gdiplus::Graphics::FromImage(backgroundBitmap);

    // 각 타일을 비트맵에 그리기
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            Gdiplus::Rect srcRect(0, 0, backgroundTileSize, backgroundTileSize);
            Gdiplus::Rect destRect(x * backgroundTileSize, y * backgroundTileSize, srcRect.Width, srcRect.Height);
            gMap->DrawImage(backgroundTile,
                destRect, srcRect.X, srcRect.Y,
                srcRect.Width, srcRect.Height,
                Gdiplus::UnitPixel);
        }
    }

    return backgroundBitmap;
}

std::vector<GameObject*> TerrainObject::CreateObjects(int rows, int cols, std::vector<int> tileData)
{
    std::vector<GameObject*> objectsList;
    // 각 타일을 비트맵에 그리기
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            int data = tileData[y * mapGridXCount + x];  // 타일 ID (0이면 빈 타일)

            switch (data)
            {
            case 241: // 사과
            {
                Apple* apple = new Apple(graphics);
                objectsList.push_back(apple);
                apple->SetupTransform(tileSize, x, y, 1, 1);
                apple->transform->SetTransform((float)(x * tileSize), (float)(y * tileSize));
                break;
            }
            default:
                break;
            }
        }
    }
    return objectsList;
}
