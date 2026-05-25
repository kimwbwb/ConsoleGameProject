#include "EnemySpawner.h"
#include "Actor/Enemy.h"
#include "Util/Util.h"
#include "Level/Level.h"

using namespace Craft;

// 적 생성할 때 사용할 글자 값
// 여기에서 사용된 static은 전역의 의마가 아니라 이 cpp파일에서만 사용하는 private의 의미
static std::string enemyType[] =
{
	";:^:;",
	"zZwZz",
	"oO@Oo",
	"<-=->",
	")qOp(",
	"(oOo)"
};

EnemySpawner::EnemySpawner()
{
	// 적 생성 타이머 설정
	timer.SetTargetTime(Util::RandomRange(2.0f, 3.0f));
}

void EnemySpawner::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 타이머 업데이트
	timer.Tick(deltaTime);

	// 경과 시간 확인
	if (!timer.IsTimeOut())
	{
		return;
	}

	// 타이머 초기화
	timer.Reset();

	// 적 생성
	SpawnEnemy();
}

void EnemySpawner::SpawnEnemy()
{
	// 적 생성
	// 적 타입의 항목 수 계산
	const int count = sizeof(enemyType) / sizeof(enemyType[0]);

	// 랜덤 인덱스
	const int index = Util::RandomRange(0, count - 1);

	// 생성 y 위치
	const int yPosition = Util::RandomRange(1, 10);

	// 적 생성 요청
	GetOwner()->SpawnActor<Enemy>(enemyType[index], yPosition);
}
