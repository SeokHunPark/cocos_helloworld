#pragma once

// Z-Orders

#define ZORDER_SEA                              0   // 바다 배경
#define ZORDER_SPRITE_BATCH_NODE_SURFACE        1
#define ZORDER_SPRITE_BATCH_NODE_CLOUD          2
#define ZORDER_SPRITE_BATCH_NODE_EXPLOSION_S    3
#define ZORDER_SPRITE_BATCH_NODE_AIR            4
#define ZORDER_SPRITE_BATCH_NODE_EXPLOSION_A    5
#define ZORDER_SPRITE_BATCH_NODE_INTERFACE      6

// Surface Z-Order
#define ZORDER_RADAR        1   // 레이더
#define ZORDER_SUBMARINE    2   // 잠수함
#define ZORDER_SHIPTAIL     3   // 배의 물결
#define ZORDER_SHIP         4   // 배
#define ZORDER_DOKDO        5   // 독도
#define ZORDER_SHADOW       6   // 항공기 그림자
#define ZORDER_WATERCOLUMN  7   // 물기둥

// Air Z-Order
#define ZORDER_BULLET           1   // 총탄
#define ZORDER_LYNX             2  // 링스헬기
#define ZORDER_HELICOPTER       3  // 공격헬기
#define ZORDER_CLOUD            4  // 구름 그림자
#define ZORDER_BOMB             5  // 폭탄
#define ZORDER_BOMBER           6  // 폭격기
#define ZORDER_FIGHTER          7  // 전투기
#define ZORDER_STRATEGYBOMBER   8  // 전략폭격기
#define ZORDER_MISSILE          9  // 미사일
#define ZORDER_PEACEEYE         10  // 피스아이 조기 경보기
#define ZORDER_NUCLEAR          11  // 핵폭탄

// Tags
#define TAG_SPRITE_BATCH_NODE_SURFACE       1000
#define TAG_SPRITE_BATCH_NODE_CLOUD         1001
#define TAG_SPRITE_BATCH_NODE_EXPLOSION_S   1002
#define TAG_SPRITE_BATCH_NODE_AIR           1003
#define TAG_SPRITE_BATCH_NODE_EXPLOSION_A   1004
#define TAG_SPRITE_BATCH_NODE_INTERFACE     1005
