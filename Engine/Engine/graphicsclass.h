////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	//bool Render(float);
	//Xu
	bool HandleMovementInput(float);
	bool Render();
	void SetTimescale(int newTimeScale);
	bool LoadModel(char*);

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;

	ModelType* m_model;
	
	ModelClass* m_Sun;
	ModelClass* m_Skybox;
	BumpModelClass* m_Mercury;
	BumpModelClass* m_Venus;
	BumpModelClass* m_Earth;
	BumpModelClass* m_Mars;
	BumpModelClass* m_Jupiter;
	BumpModelClass* m_Saturn;
	BumpModelClass* m_Uranus;
	BumpModelClass* m_Neptune;
	int m_vertexCount, m_indexCount;

private:
	float timeScale;
	int oldMouseX, oldMouseY;
	
};

#endif