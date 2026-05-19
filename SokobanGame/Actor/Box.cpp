#include "Box.h"

Box::Box(const Craft::Vector2& position)
	:Actor("B", position, Craft::Color::Red)
{
	// Ground/Target 액터와 겹쳤을 때 박스가 그려지도록 우선 순위 설정
	sortingOrder = 3;
}
