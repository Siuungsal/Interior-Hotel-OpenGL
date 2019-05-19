#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint tshaderProgram, tVBO, tVAO, tEBO, ttexture, tVBO2, tVAO2, tEBO2, ttexture2, stexture, stexture2;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	float angle = 0;
	float angleStayX = 1.57;
	float angleStayY = 90;

	bool power = false;
	int oldKeyState;
	int channel = 0;

	const char* textureOn = "Spongebob.png";
	const char* textureOn1 = "Avenger.png";
	const char* textureOn2 = "Chaplin.png";
	const char* textureOn3 = "Mahabarata1.png";

	const char* textureOff = "tv.png";

	GLuint lantaiVBO, lantaiVAO, lantaiEBO, lantaiTexture;
	GLuint tembokVBO, tembokVAO, tembokEBO, tembokTexture;
	GLuint windowVBO, windowVAO, windowEBO, windowTexture;
	GLuint kakimeja1VBO, kakimeja1VAO, kakimeja1EBO, kakimeja1Texture;
	GLuint kakimeja2VBO, kakimeja2VAO, kakimeja2EBO, kakimeja2Texture;
	GLuint mejaVBO, mejaVAO, mejaEBO, mejaTexture;
	GLuint tvsupVBO, tvsupVAO, tvsupEBO, tvsupTexture;
	GLuint tvVBO, tvVAO, tvEBO, tvTexture;
	GLuint kipasVBO, kipasVAO, kipasEBO, texKipasID, texNormKipasID;
	GLuint sofaVBO, sofaVAO, sofaEBO, sofaTexture;
	GLuint sofaBwhVBO, sofaBwhVAO, sofaBwhEBO, sofaBwhTexture;
	GLuint sofaKiriVBO, sofaKiriVAO, sofaKiriEBO, sofaKiriTexture;
	GLuint sofaKananVBO, sofaKananVAO, sofaKananEBO, sofaKananTexture;
	
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildTexturedCube();
	void BuildTexturedPlane();
	void DrawTexturedCube();
	void DrawTexturedPlane();

	void BuildLantai();
	void DrawLantai();
	void Buildtembok();
	void Drawtembok();
	void Buildwindow();
	void Drawwindow();
	void Buildkakimeja1();
	void Drawkakimeja1();
	void Buildkakimeja2();
	void Drawkakimeja2();
	void Buildmeja();
	void Drawmeja();
	void Buildtvsup();
	void Drawtvsup();
	void Buildtv();
	void Drawtv();
	void Buildsofa();
	void Drawsofa();
	void BuildsofaBwh();
	void DrawsofaBwh();
	void BuildsofaKiri();
	void DrawsofaKiri();
	void BuildsofaKanan();
	void DrawsofaKanan();

	void BuildKipas();
	void DrawKipas(float x, float y, float z, float deg, int rotX, int rotY, int rotZ);

	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};

