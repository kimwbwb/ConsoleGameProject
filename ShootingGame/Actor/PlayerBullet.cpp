#include "PlayerBullet.h"

using namespace Craft;

PlayerBullet::PlayerBullet(const Craft::Vector2& position)
	: super("@", position, Color::Blue),
	yPosition(static_cast<float>(position.y))
{
}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 위치 이동 처리
	yPosition -= moveSpeed * deltaTime;

	// 좌표 검사
	if (yPosition < 0.0f)
	{
		// 삭제 처리
		Destroy();
		return;
	}

	// 액터의 위치로 변환
	Vector2 newPosition = position;
	newPosition.y = static_cast<int>(yPosition);

	// 위치 설정
	SetPosition(newPosition);

}
