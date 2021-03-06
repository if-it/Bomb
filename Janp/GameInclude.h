#pragma once
#include"Controller.h"
#include"Draw.h"
#include"Map.h"
#include"Player.h"
#include"Fuse.h"
#include"BombMana.h"
#include"ExplosionMana.h"
#include"Enemy1Mana.h"
#include "Enemy2.h"
#include"UI.h"
#include"SaveMana.h"
#include"ItemMana.h"
#include"BackMap.h"
#include"BackMap2.h"
#include"Dust.h"
#include"MapBombMana.h"
#include"MapSwitch.h"
#include"Enemy3Mana.h"
#include"SideExplosionMana.h"
#include"Enemy4Mana.h"
#include"OrbitBomb.h"
#include"FrontMap.h"
#include"AroundEffectMana.h"
#include"Text.h"
#include"SkillEffectMana.h"
#include"BombSpawnEffect.h"
#include"BombBlowEffectMana.h"
#include "OpeningScene.h"

class GameInclude :public Draw
{
public:
	GameInclude();
	~GameInclude();
	int ConCheck();
protected:
	void ControllerOnly(bool on);
	void ParentInit();
	bool SceneChangeSeb(int seb);
	bool SceneChangeAdd(int add);
	bool SceneChanger(int a);
	void Shake(Count& count, int num, Vector2 shakeMax, std::vector<std::vector<int>>& map);


	Controller* con = new Controller();
	Key* key = new Key();
	Mouse* mouse = new Mouse();
	Load* load = new Load();
	Map* map = new Map();
	Player* player = new Player();
	Collision* coll = new Collision();
	Fuse* fuse = new Fuse();
	BombMana* bombMana = new BombMana();
	ExplosionMana* exMana = new ExplosionMana();
	Enemy1Mana* enemy1Mana = new Enemy1Mana();
	Enemy2* enemy2 = new Enemy2();
	UI* ui = new UI();
	SaveMana* saveMana = new SaveMana();
	ItemMana* itemMana = new ItemMana();
	BackMap* backMap = new BackMap();
	BackMap2* backMap2 = new BackMap2();
	Dust* dust = new Dust();
	MapBombMana* mapBombMana = new MapBombMana();
	MapSwitch* mapSwitch = new MapSwitch();
	Enemy3Mana* enemy3Mana = new Enemy3Mana();
	SideBomb* sideBomb = new SideBomb();
	SideExplosionMana* sideExMana = new SideExplosionMana();
	Enemy4Mana* enemy4Mana = new Enemy4Mana();
	RockEffectMana* rockEffeMana = new RockEffectMana();
	RockAttackMana* rockAttackMana = new RockAttackMana();
	HpDropItemMana* hpDropItemMana = new HpDropItemMana();
	OrbitBomb* orbitBomb = new OrbitBomb();
	BlockParticleMana* blockParticleMana = new BlockParticleMana();
	FrontMap* frontMap = new FrontMap();
	AroundEffectMana* aroundEffeMana = new AroundEffectMana();
	Text* text = new Text();
	BombSpawnEffect* bombSpawnEffect = new BombSpawnEffect();
	BombBlowEffectMana* bombBlowEffectMana = new BombBlowEffectMana();



	SkillEffectMana* skillEffectMana;
	OpeningScene* openingScene;

	bool controllerOnly;
	bool drawScene;
	bool sceneChange;
	int loadCount;
	int pal;
	int haikei;
	int title;
	int cursor;
	int text_Play_Tex;
	int text_Exit_Tex;
	int text_Option_Tex;
	int text_Options_Tex[8];
	int text_On_Off[2];
	int text_Num[10];
	int bgm1;

	enum SCENE
	{
		INIT,
		FIRST_SCENE,
		LOAD,
		UNLOAD,
		TITLE,
		TUTORIAL,
		PALYINIT,
		PLAY,
		GAMEOVER,
		GAMECLEAR,
		RESULT,
		DEMO,
		DEMOINIT,
		SELECT,
		MAPSET,
		PLAYINIT,
		PLAYINIT2,
		ENDING,
		OPTION,
		MENU,
		OPENING_INIT,
		OPENING_INIT2,
		OPENING,
		TALKINIT,
		TALK,
	};
	int scene;
	int before_Scene;
	int stage;
	bool stageChange;
	int title_Flg;
	int play_option_Flg;
	bool title_To_Play;
	Count shake_Counter;

	Vector2 sc;
	Vector2 shake;
	std::vector<GameObject*>coll_List;
};

