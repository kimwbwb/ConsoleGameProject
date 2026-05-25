#pragma once

#include "Actor/Actor.h"
#include "Util/Timer.h"

class EnemySpawner : public Craft::Actor
{
	// RTTI 등록
	TYPE_DECLARATIONS(EnemySpawner,Actor)

public:
	EnemySpawner();
	~EnemySpawner() = default;
	
private:
	// Tick이벤트
	virtual void Tick(float deltaTime) override;

	// 적 생성 함수
	void SpawnEnemy();

private:
	// 생성 타이머
	Timer timer;
};

