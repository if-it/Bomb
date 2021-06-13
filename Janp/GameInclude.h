#pragma once
#include"Controller.h"
#include"Draw.h"
#include"Load.h"
#include"Map.h"
#include"Player.h"
#include"Fuse.h"
#include"MapExColl.h"
#include"MapBombColl.h"
#include"ParticleMana.h"
#include"BombMana.h"
#include"ExplosionMana.h"

class GameInclude :public Draw
{
public:
	GameInclude();
	~GameInclude();
	int ConCheck();
protected:
	void ControllerOn(bool on);
	void ParentInit();
	bool SceneChangeSeb(int seb);
	bool SceneChangeAdd(int add);
	bool SceneChanger(int a);
	void Shake(Count& count, int num, Vector2 shakeMax);


	Controller* con = new Controller();
	Key* key = new Key();
	Mouse* mouse = new Mouse();
	Load*load = new Load();
	Map*map = new Map();
	Player*player = new Player();
	Collision*coll = new Collision();
	Fuse* fuse = new Fuse();
	//MapExColl* mapExColl = new MapExColl();
	//MapBombColl* mapBombColl = new MapBombColl();
	ParticleMana* particleMana = new ParticleMana();
	BombMana* bombMana = new BombMana();
	BombMana* playerBombMana = new BombMana();
	ExplosionMana* exMana = new ExplosionMana();

	bool controllerOnly;
	bool drawScene;
	bool sceneChange;
	int loadCount;
	int pal;
	int haikei;
	int clear;
	int title;
	int button;
	int stick;
	int bgm1;

	enum SCENE
	{
		INIT,
		OPENING,
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
		MAPSET2,
		PLAYINIT,

	};
	int scene;
	int stage;
	bool stageChange;
	bool titleFlg;
	bool title_To_Play;
	Count bombShake;

	Vector2 sc;
	Vector2 shake;
};

