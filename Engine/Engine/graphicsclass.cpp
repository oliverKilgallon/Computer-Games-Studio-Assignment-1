////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;

	//Sol
	m_Sun = 0;

	//Rocky planets
	m_Mercury = 0;
	m_Venus = 0;
	m_Earth = 0;
	m_Mars = 0;

	//Gas Giants
	m_Jupiter = 0;
	m_Saturn = 0;
	m_Uranus = 0;
	m_Neptune = 0;
	timeScale = 1;
	
	//Skybox
	m_Skybox = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	result = LoadModel("../Engine/data/Models/Planet.txt");
	if (!result) 
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -50.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, 50.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}	
	// Initialize the light object.
	m_Light->SetAmbientColor(0.25f, 0.18f, 0.17f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(40.0f);

	// Create the Sun model object.
	m_Sun = new ModelClass;
	if (!m_Sun)
	{
		return false;
	}

	// Initialize the Sun model object.
	result = m_Sun->Initialize(m_D3D->GetDevice(), "../Engine/data/Models/Planet.txt", L"../Engine/data/Textures/Albedo/lowResSun.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Sun model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Mercury model object.
	m_Mercury = new BumpModelClass;
	if (!m_Mercury)
	{
		return false;
	}

	// Initialize the Mercury model object.
	result = m_Mercury->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Mercury.dds", L"../Engine/data/Textures/Normals/MercuryNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Mercury model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Venus model object.
	m_Venus = new BumpModelClass;
	if (!m_Venus)
	{
		return false;
	}

	// Initialize the Venus model object.
	result = m_Venus->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Venus.dds", L"../Engine/data/Textures/Normals/VenusNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Venus model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Earth model object.
	m_Earth = new BumpModelClass;
	if (!m_Earth)
	{
		return false;
	}

	// Initialize the Earth model object.
	result = m_Earth->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Earth.dds", L"../Engine/data/Textures/Normals/EarthNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Earth model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Mars model object.
	m_Mars = new BumpModelClass;
	if (!m_Mars)
	{
		return false;
	}

	// Initialize the Mars model object.
	result = m_Mars->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Mars.dds", L"../Engine/data/Textures/Normals/MarsNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Mars model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Jupiter model object.
	m_Jupiter = new BumpModelClass;
	if (!m_Jupiter)
	{
		return false;
	}

	// Initialize the Jupiter model object.
	result = m_Jupiter->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Jupiter.dds", L"../Engine/data/Textures/Normals/JupiterNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Jupiter model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Saturn model object.
	m_Saturn = new BumpModelClass;
	if (!m_Saturn)
	{
		return false;
	}

	// Initialize the Saturn model object.
	result = m_Saturn->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Saturn.dds", L"../Engine/data/Textures/Normals/SaturnNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Saturn model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Uranus model object.
	m_Uranus = new BumpModelClass;
	if (!m_Uranus)
	{
		return false;
	}

	// Initialize the Uranus model object.
	result = m_Uranus->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Uranus.dds", L"../Engine/data/Textures/Normals/SaturnNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Uranus model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Neptune model object.
	m_Neptune = new BumpModelClass;
	if (!m_Neptune)
	{
		return false;
	}

	// Initialize the Neptune model object.
	result = m_Neptune->Initialize(m_D3D->GetDevice(), m_model, L"../Engine/data/Textures/Albedo/Neptune.dds", L"../Engine/data/Textures/Normals/NeptuneNormal.dds", m_vertexCount, m_indexCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Neptune model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Skybox model object.
	m_Skybox = new ModelClass;
	if (!m_Skybox)
	{
		return false;
	}

	// Initialize the skybox model object.
	result = m_Skybox->Initialize(m_D3D->GetDevice(), "../Engine/data/Models/Planet.txt", L"../Engine/data/Textures/Albedo/Skybox.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the skybox model object.", L"Error", MB_OK);
		return false;
	}
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.

	if (m_Sun)
	{
		m_Sun->Shutdown();
		delete m_Sun;
		m_Sun = 0;
	}

	if (m_Skybox)
	{
		m_Skybox->Shutdown();
		delete m_Skybox;
		m_Skybox = 0;
	}

	if (m_Mercury)
	{
		m_Mercury->Shutdown();
		delete m_Mercury;
		m_Mercury = 0;
	}

	if (m_Venus)
	{
		m_Venus->Shutdown();
		delete m_Venus;
		m_Venus = 0;
	}

	if (m_Earth)
	{
		m_Earth->Shutdown();
		delete m_Earth;
		m_Earth = 0;
	}

	if (m_Mars)
	{
		m_Mars->Shutdown();
		delete m_Mars;
		m_Mars = 0;
	}

	if (m_Jupiter)
	{
		m_Jupiter->Shutdown();
		delete m_Jupiter;
		m_Jupiter = 0;
	}

	if (m_Saturn)
	{
		m_Saturn->Shutdown();
		delete m_Saturn;
		m_Saturn = 0;
	}

	if (m_Uranus)
	{
		m_Uranus->Shutdown();
		delete m_Uranus;
		m_Uranus = 0;
	}

	if (m_Neptune)
	{
		m_Neptune->Shutdown();
		delete m_Neptune;
		m_Neptune = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	if (m_model) 
	{
		delete[] m_model;
		m_model = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsOnePressed();
	if(keyDown)this->SetTimescale(1);

	keyDown = m_Input->IsTwoPressed();
	if (keyDown)this->SetTimescale(2);

	keyDown = m_Input->IsThreePressed();
	if (keyDown)this->SetTimescale(3);

	keyDown = m_Input->IsFourPressed();
	if (keyDown)this->SetTimescale(4);

	keyDown = m_Input->IsZeroPressed();
	if (keyDown)this->SetTimescale(0);

	int MouseX, MouseY;

	m_Input->GetMouseLocation(MouseX, MouseY);

	m_Position->MouseHorizontal(MouseX - oldMouseX);
	m_Position->MouseVertical(MouseY - oldMouseY);

	oldMouseX = MouseX;
	oldMouseY = MouseY;

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

void GraphicsClass::SetTimescale(int newTimeScale)
{
	this->timeScale = newTimeScale;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;
	XMFLOAT3 cameraPosition;

	static float rotation = 0.0f;

	static float mercuryOrbitSpeed = 0.0f;
	static float mercuryYOffset = 0.0f;

	static float venusOrbitSpeed = 0.0f;
	static float venusYOffset = 0.0f;

	static float earthOrbitSpeed = 0.0f;
	static float earthYOffset = 0.0f;

	static float marsOrbitSpeed = 0.0f;
	static float marsYOffset = 0.0f;

	static float jupiterOrbitSpeed = 0.0f;
	static float jupiterYOffset = 0.0f;

	static float saturnOrbitSpeed = 0.0f;
	static float saturnYOffset = 0.0f;

	static float uranusOrbitSpeed = 0.0f;
	static float uranusYOffset = 0.0f;

	static float neptuneOrbitSpeed = 0.0f;
	static float neptuneYOffset = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();


	// Update each planet's yOffset variable and orbitSpeed variable each frame.
	mercuryYOffset += (float)XM_PI * -0.0001f * m_Timer->GetTime();
	mercuryOrbitSpeed += (float)XM_PI * 0.00006f * m_Timer->GetTime();

	venusYOffset += (float)XM_PI * 0.000035f * m_Timer->GetTime();
	venusOrbitSpeed += (float)XM_PI * 0.00005f * m_Timer->GetTime();

	earthYOffset += (float)XM_PI * 0.000025f * m_Timer->GetTime();
	earthOrbitSpeed += (float)XM_PI * 0.00003f * m_Timer->GetTime();

	marsYOffset += XM_PI * -0.00005f * m_Timer->GetTime();
	marsOrbitSpeed += XM_PI * 0.0000225f * m_Timer->GetTime();

	jupiterYOffset += (float)XM_PI * 0.000007f * m_Timer->GetTime();
	jupiterOrbitSpeed += (float)XM_PI * 0.0000035f * m_Timer->GetTime();

	saturnYOffset += (float)XM_PI * 0.00003f * m_Timer->GetTime();
	saturnOrbitSpeed += (float)XM_PI * 0.0000055f * m_Timer->GetTime();

	uranusYOffset += (float)XM_PI * -0.00002f * m_Timer->GetTime();
	uranusOrbitSpeed += (float)XM_PI * 0.0000015f * m_Timer->GetTime();

	neptuneYOffset += (float)XM_PI * 0.00002f * m_Timer->GetTime();
	neptuneOrbitSpeed += (float)XM_PI * 0.000001f * m_Timer->GetTime();



	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the rotation and translation of the Mars model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.1f, 0.1f, 0.1f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 1.4f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 130.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-marsOrbitSpeed * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10.0f * sin(marsYOffset) * timeScale, 50.0f));


		// Render the mars model using the light shader.
		m_Mars->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Mars->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Mars->GetColorTexture(), m_Mars->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Earth model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.15f, 0.15f, 0.15f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 2.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 100.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-earthOrbitSpeed * 1.25) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 50.0f));


		// Render the earth model using the light shader.
		m_Earth->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Earth->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Earth->GetColorTexture(), m_Mars->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Uranus model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.4f, 0.4f, 0.4f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(1.55f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationZ((-rotation / 40.0f) * timeScale));

		//How far from the sun
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 405.0f));

		//Orbit around sun
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-uranusOrbitSpeed * timeScale));

		//Offset origin point and vary y-pos
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, -cos(uranusOrbitSpeed) * timeScale, 50.0f));


		// Render the uranus model using the light shader.
		m_Uranus->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Uranus->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Uranus->GetColorTexture(), m_Mars->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the sun model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.3f, 0.3f, 0.3f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((rotation / 50.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 50.0f));


		// Render the sun model using the light shader.
		m_Sun->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Sun->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Sun->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the skybox model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(-30.0f, -30.0f, -30.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((rotation / 180.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 50.0f));


		// Render the sun model using the light shader.
		m_Skybox->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Skybox->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Skybox->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Mercury model
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.04f, 0.04f, 0.04f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 45.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 40.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-mercuryOrbitSpeed * 2) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10.0f * sin(mercuryYOffset) * timeScale, 50.0f));


		// Render the Mercury model using the light shader.
		m_Mercury->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Mercury->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Mercury->GetColorTexture(), m_Mercury->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Venus model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.10f, 0.10f, 0.10f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 2.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 70.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-venusOrbitSpeed * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10 * -cos(venusYOffset) * timeScale, 50.0f));


		// Render the earth model using the light shader.
		m_Venus->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Venus->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Venus->GetColorTexture(), m_Venus->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Jupiter model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.8f, 0.7f, 0.8f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 30.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 200.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-jupiterOrbitSpeed * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10 * -cos(jupiterYOffset) * timeScale, 50.0f));


		// Render the earth model using the light shader.
		m_Jupiter->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Jupiter->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Jupiter->GetColorTexture(), m_Jupiter->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Saturn model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.625f, 0.6f, 0.625f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 50.0f) * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 300.0f));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-saturnOrbitSpeed * timeScale));

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10 * -sin(saturnYOffset) * timeScale, 50.0f));


		// Render the earth model using the light shader.
		m_Saturn->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Saturn->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Saturn->GetColorTexture(), m_Saturn->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Setup the rotation and translation of the Neptune model.
	{
		m_D3D->GetWorldMatrix(worldMatrix);

		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.4f, 0.4f, 0.4f));

		//Rotation speed round self
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY((-rotation / 30.0f) * timeScale));

		//Distance from sun
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 500.0f));

		//Orbit speed
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(-neptuneOrbitSpeed * timeScale));

		//Offset from origin and y-pos variation
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 10 * -cos(neptuneYOffset) * timeScale, 50.0f));


		// Render the earth model using the light shader.
		m_Neptune->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Neptune->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Neptune->GetColorTexture(), m_Neptune->GetNormalMapTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}

bool GraphicsClass::LoadModel(char* filename) 
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.  If it could not open the file then exit.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}