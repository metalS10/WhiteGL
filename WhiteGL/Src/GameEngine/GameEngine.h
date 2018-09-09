/**
*@file	GameEngine.h
*/
#pragma once
#include "../Constants.h"
#include "../RendTexture/Render.h"
#include "../Data/Animation/Animation.h"
#include "../GamePad.h"
#include "../GLFWEW/GLFWEW.h"
#include "../interpreter/interpreter.h"

//�|���S���ݒ�Ɏg���|���S������
enum POLY_TYPE :GLuint
{
	TRIANGLE	= 0,
	QUAD		= 1,
};

class CCharacter;
class CGameEngine
{
private :
	CRenderer* renderer = NULL;
	std::vector<CAnimation*>* m_pAnim = NULL;
	GLFWwindow* m_Window = NULL;
	bool isInitialized = false;

	int countMap = 0;

	int EnemyTexID = START_ENEMY_TEXTURE_NUMBER;

	bool actionone1 = false;
public:
	float m_hitStop = 0.0f;
	//�Q�[�����t���O(�Q�[�����I������Ƃ��ɉ���)
	bool gameNow = true;

public:
	CGameEngine() {}
	~CGameEngine(){}
	GLFWwindow* init(int w, int h, const char* file);
	void renderInit();		//�`��̏�����
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color);	//�e�N�X�`���ݒ�
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect);				//�F�ύX�Ȃ�overload
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer);	//�e�N�X�`���ݒ�(���C���[�ݒ肠��)
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, LAYER layer);				//�F�ύX�Ȃ�overload(���C���[�ݒ肠��)
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype);		//�w�i�O�p�|���S���̐ݒ�(vertex(����X,����Y,Width,Height))
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const LAYER layer);		//layer�ݒ肠��w�i�O�p�|���S���̐ݒ�(vertex(����X,����Y,Width,Height))
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const GLuint tag);		//layer�ݒ肠��w�i�O�p�|���S���̐ݒ�(vertex(����X,����Y,Width,Height))��ɕҏW����ꍇ�̂��߂�tag�w��
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const LAYER layer, const GLuint tag);		//layer�ݒ肠��w�i�O�p�|���S���̐ݒ�(vertex(����X,����Y,Width,Height))��ɕҏW����ꍇ�̂��߂�tag�w��
	void setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number);	//�w�i�O�p�|���S���̈ʒu�Đݒ�(X���W�̂�)
	void setPolyPos(const CVec2 vertex, const GLuint tag);	//�|���S���̈ʒu�Đݒ�
	void setPolyScale(const CVec2 scale , const GLuint tag);	//�|���S���̃X�P�[���Đݒ�
	void setPolyPosX(const float vertex, const GLuint tag);	//�|���S����X�ʒu�Đݒ�
	void setPolyAngle(const float angle, const GLuint tag);	//�|���S���̉�]�ݒ�
	void setPolyColor(const CVec4 color, const GLuint tag);	//�|���S���̐F�ݒ�
	void addPolyAngle(const float angle, const GLuint tag);	//�|���S���̉�]�ݒ�
	float getPolyAngle(const GLuint tag);	//�|���S���̉�]�Q�b�g
	CVec2 getPolyScale(const GLuint tag);	//�|���S���̃X�P�[���擾
	CVec4 getPolyColor(const GLuint tag);	//�|���S���̐F�擾
	void setChipAnim(CAnimation *&&_val);		//Chip�A�j���[�V�����ݒ�
	void setChipData(GLuint texID, CVec4 rectData);	
	void update();
	void update60();
	void render();		//�@�`�揈��
	const GamePad& GetGamePad() const;
	static CGameEngine& Instance();
	void setTextureRect(const CVec4 mrect,const GLuint texID);
	void setTexPosition(CVec2 pos, GLuint texID);
	void setTexScale(CVec2 scale,GLuint texID);
	void setTexScaleAtTag(const CVec2 scale,const GLuint tag);
	void setTexColorAtTag(const CVec4 color,const GLuint tag);
	void deleteTexture(const GLuint texID);
	void deletePoly(const GLuint tag);
	void allTextureDelete();
	void allTextureDeletenotPlayer();
	void SetProgressBarWH(const GLuint texID, const CVec4 Rect, const CVec2 position);

	void loadTMXMap(CLayerData layerData[MAX_LAYER_NUMBER], int width, int height);
	void TMXMapSetPos(float x, float y);
	void layerSetPos(float x, float y, GLuint texID);

	//�A�N�V����
	bool ActionStage(const GLuint texID, const float fadeInterval, const bool fade);
	void* TextureFade(const GLuint texID, const bool out ,const float fadeInterval);
	bool getFadeEnd(const GLuint tag);

	CRenderer* getRenderer();

	void HitStop(float time);
	void GameEnd();

	/**
	*	mode
	*0.Random
	*1.Up
	*2.doubleUp
	*/
	void notesAction(int mode);
	//beats�ɍ��킹��A�N�V����(0:Vert,1:Color)
	void polygonAction(const GLuint tag,const GLuint mode);




};