#pragma once
/**
*	Constants.h
*		2017/9/30	Mats
*		ϸۂȂǂ�ݒ肷���
*/

//��΃p�X
#define PASS "Resources/"
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif
//�폜
#define SAFE_DELETE(p_)if(p_){delete p_;p_ = NULL;}
//��ʃT�C�Y
#define WINDOW_SIZE 1280,720
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_RIGHT WINDOW_WIDTH
#define WINDOW_LEFT 0
#define WINDOW_TOP WINDOW_HEIGHT
#define WINDOW_BOTTOM 0
//�e�N�X�`���ő吔
#define MAX_TEXTURE_NUMBER 10000
//���C���[�ő吔(�g��Ȃ��ꍇ��0)
#define MAX_LAYER_NUMBER 3
//�e�N�X�`��ID�̐ݒ�---------------------------------------------------------------
//�e
#define START_BULLET_TEXTURE_NUMBER 1000
//�G
#define START_ENEMY_TEXTURE_NUMBER START_BULLET_TEXTURE_NUMBER + 1000
//�G�U��
#define START_ENEMY_BULLET_TEXTURE_NUMBER START_ENEMY_TEXTURE_NUMBER+1000
//�M�~�b�N
#define START_GIMMICK_TEXTURE_NUMBER START_ENEMY_BULLET_TEXTURE_NUMBER + 1000
//�}�b�v�`��
#define START_MAP_TEXTURE_NUMBER 500
//--------------------------------------------------------------------------------

//�e�N�X�`��ID
#define PLAYER_ID				3	//Player
#define UI_BACK_ID				4	//UIBack
#define OUTLINE_HP_ID			5	//HPWaku
#define OUTLINE_DP_ID			6	//DPWaku
#define BAR_HP_ID				7	//HPBar
#define BAR_DP_ID				8	//DPBar
#define ENEMY_STATS_ID			9	//ENEMYStats
#define OUTLLINE_ENEMYHP_ID		10	//EHPBarWaku
#define BAR_ENEMYHP_ID			11	//EHPBar

#define UI_ID PLAYER_ID UI_BACK_ID OUTLINE_HP_ID OUTLINE_DP_ID BAR_HP_ID BAR_DP_ID ENEMY_STATS_ID OUTLLINE_ENEMYHP_ID BAR_ENEMYHP_ID



//�v���C���[
#define IMAGE_PLAYER PASS"player.png"

//�U��
#define IMAGE_NORMALATTACK PASS"Attack/attack_sword.png"
#define IMAGE_GETSUGATENSHO PASS"Attack/getsugatenshou.png"

//�G
#define IMAGE_ENEMY PASS"Images/Enemy/Enemy.png"
#define IMAGE_NOKONOKO PASS""
#define IMAGE_PATAPATA PASS""
#define IMAGE_KILLER PASS""
#define IMAGE_TROI PASS"Images/Enemy/enemy_Troi.png"

//�M�~�b�N
#define IMAGE_DAMAGEBLOCK PASS"Images/damageBlock.png"
#define IMAGE_ROLLBLOCK PASS""
#define IMAGE_TIKUWABLOCK PASS""
#define IMAGE_NOTEBLOCK PASS""
#define IMAGE_HATENABLOCK PASS""
#define IMAGE_WORP PASS"Images/Gimmick/worp.png"

//�e
#define IMAGE_NORMAL_FIRE PASS"Images/normalBullet.png"
#define IMAGE_FIREBALL PASS""

//UI
#define IMAGE_GAMEUI	PASS"Images/UI/WhiteUI.png"
#define IMAGE_STAGEEND	PASS"Images/UI/StageEnd.png"

//�}�b�v
#define MAP_PASS PASS"mapData/"
#define MAP_DATA_1 PASS"mapData/1_MapData.tmx"
#define MAP_DATA_2 PASS"mapData/MapData2.tmx"

//�w�i
#define TITLE_BG PASS"Images/BG/title.png"
#define MAIN_BG PASS"Images/BG/black0087.png"
#define MAIN_MOVEBG PASS"Images/BG/p1.png"

//�^�O
#define TAG_PLAYER_1 1001

//Math
#define M_PI       3.14159265358979323846f   // pi
//etc
#define CC_DLL     __declspec(dllimport)

typedef enum TMXTileFlags_ {
    kTMXTileHorizontalFlag  = 0x80000000,
    kTMXTileVerticalFlag    = 0x40000000,
    kTMXTileDiagonalFlag    = 0x20000000,
    kTMXFlipedAll           = (kTMXTileHorizontalFlag|kTMXTileVerticalFlag|kTMXTileDiagonalFlag),
    kTMXFlippedMask         = ~(kTMXFlipedAll)
} TMXTileFlags;