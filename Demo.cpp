#include "Demo.h"



Demo::Demo() {

}


Demo::~Demo() {
}





void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	tshaderProgram = BuildShader("multipleLight.vert", "multipleLight.frag", nullptr);
	//BuildTexturedCube();
	//BuildTexturedPlane();
	BuildLantai();
	Buildtembok();
	Buildwindow();
	Buildkakimeja1();
	Buildkakimeja2();
	Buildmeja();
	Buildtvsup();
	Buildtv();
	Buildsofa();
	BuildsofaBwh();
	BuildsofaKiri();
	BuildsofaKanan();
	InitCamera();
	BuildKipas();

}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &tVAO);
	//glDeleteBuffers(1, &tVBO);
	//glDeleteBuffers(1, &tEBO);
	//glDeleteVertexArrays(1, &tVAO2);
	//glDeleteBuffers(1, &tVBO2);
	//glDeleteBuffers(1, &tEBO2);
	glDeleteVertexArrays(1, &lantaiVAO);
	glDeleteBuffers(1, &lantaiVBO);
	glDeleteBuffers(1, &lantaiEBO);

	glDeleteVertexArrays(1, &tembokVAO);
	glDeleteBuffers(1, &tembokVBO);
	glDeleteBuffers(1, &tembokEBO);

	glDeleteVertexArrays(1, &windowVAO);
	glDeleteBuffers(1, &windowVBO);
	glDeleteBuffers(1, &windowEBO);

	glDeleteVertexArrays(1, &kakimeja1VAO);
	glDeleteBuffers(1, &kakimeja1VBO);
	glDeleteBuffers(1, &kakimeja1EBO);

	glDeleteVertexArrays(1, &kakimeja2VAO);
	glDeleteBuffers(1, &kakimeja2VBO);
	glDeleteBuffers(1, &kakimeja2EBO);

	glDeleteVertexArrays(1, &mejaVAO);
	glDeleteBuffers(1, &mejaVBO);
	glDeleteBuffers(1, &mejaEBO);


	glDeleteVertexArrays(1, &tvsupVAO);
	glDeleteBuffers(1, &tvsupVBO);
	glDeleteBuffers(1, &tvsupEBO);

	glDeleteVertexArrays(1, &tvVAO);
	glDeleteBuffers(1, &tvVBO);
	glDeleteBuffers(1, &tvEBO);

	glDeleteVertexArrays(1, &kipasVAO);
	glDeleteBuffers(1, &kipasVBO);
	glDeleteBuffers(1, &kipasEBO);

	glDeleteVertexArrays(1, &sofaVAO);
	glDeleteBuffers(1, &sofaVBO);
	glDeleteBuffers(1, &sofaEBO);

	glDeleteVertexArrays(1, &sofaBwhVAO);
	glDeleteBuffers(1, &sofaBwhVBO);
	glDeleteBuffers(1, &sofaBwhEBO);

	glDeleteVertexArrays(1, &sofaKiriVAO);
	glDeleteBuffers(1, &sofaKiriVBO);
	glDeleteBuffers(1, &sofaKiriEBO);

	glDeleteVertexArrays(1, &sofaKananVAO);
	glDeleteBuffers(1, &sofaKananVBO);
	glDeleteBuffers(1, &sofaKananEBO);

}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		/*if (fovy < 90) {
			fovy += 0.0001f;
		}*/
		channel--;
		if (channel < 0) {
			channel = 3;
		}
		if (channel > 3) {
			channel = 0;
		}
		Buildtv();
		Drawtv();
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		/*if (fovy > 0) {
			fovy -= 0.0001f;
		}*/
		channel++;
		if (channel < 0) {
			channel = 3;
		}
		if (channel >= 4) {
			channel = 0;
		}
		Buildtv();
		Drawtv();
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);

	int newKeyState = glfwGetKey(window, GLFW_KEY_SPACE);
	if (newKeyState == GLFW_RELEASE && oldKeyState == GLFW_PRESS) {
		power = !power;
		Buildtv();
		Drawtv();
	}

	oldKeyState = newKeyState;

}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 1000);
}


void Demo::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 1.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.01f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}



void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->tshaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::vec3 cameraPos = glm::vec3(0, 3, 3);
	glm::vec3 cameraFront = glm::vec3(0, -1, -1);
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->tshaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes
	GLint viewPosLoc = glGetUniformLocation(this->tshaderProgram, "viewPos");
	glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);

	glUniform3f(glGetUniformLocation(this->tshaderProgram, "dirLight.direction"), 0.0f, -1.0f, -1.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "dirLight.specular"), 0.1f, 0.1f, 0.1f);
	// point light 1
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].position"), 0.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].ambient"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[0].quadratic"), 0.032f);
	// point light 2
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].position"), -2.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[1].quadratic"), 0.032f);
	// point light 3
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].position"), 2.0f, 3.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[2].quadratic"), 0.032f);
	// point light 4
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].position"), 0.0f, 3.0f, 2.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "pointLights[3].quadratic"), 0.032f);
	// spotLight
	glUniform3fv(glGetUniformLocation(this->tshaderProgram, "spotLight.position"), 1, &cameraPos[0]);
	glUniform3fv(glGetUniformLocation(this->tshaderProgram, "spotLight.direction"), 1, &cameraFront[0]);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(this->tshaderProgram, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(this->tshaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	
	//DrawTexturedCube();
	//DrawTexturedPlane();
	DrawLantai();
	Drawtembok();
	Drawwindow();
	Drawkakimeja1();
	Drawkakimeja2();
	Drawmeja();
	Drawtvsup();
	Drawtv();
	Drawsofa();
	DrawsofaBwh();
	DrawsofaKiri();
	DrawsofaKanan();
	//DrawKipas(1, 1.5, 2.1, 2 * glfwGetTime(), 0, 0, 1);
	DrawKipas(0, 1.5, 2.1, 2 * glfwGetTime(), 0, 0, 1);
	//DrawKipas(-1, 1.5, 2.1, 2 * glfwGetTime(), 0, 0, 1);

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildKipas()
{
	glGenTextures(1, &texKipasID);
	glBindTexture(GL_TEXTURE_2D, texKipasID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kipas.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	float vertices[] = {
		// format position, tex coords
		// bottom
		-0.09, 0.09,	0,	0,  0,	1,	0.41, 0.58,
		0.09, -0.09,	0,	0,  0,	1,	0.58, 0.41,
		-0.09, -0.09,	0,	0,  0,	1,	0.41, 0.41,

		0.53, 0.09,	0,	0,  0,	1,	0.99, 0.58,
		0.09, -0.09,	0,	0,  0,	1,	0.58, 0.41,
		0.09, 0.09,	0,	0,  0,	1,	0.58, 0.58,

		-0.09, 0.53,	0,	0,  0,	1,	0.41, 0.99,
		0.09, 0.09,	0,	0,  0,	1,	0.58, 0.58,
		-0.09, 0.09,	0,	0,  0,	1,	0.41, 0.58,

		-0.53, -0.09375,	0,	0,  0,	1,	9.99,	0.41,
		-0.09, 0.09375,	0,	0,  0,	1,	0.4117822,	0.58,
		-0.09, -0.09375,	0,	0,  0,	1,	0.41,	0.41,

		0.09, -0.53125,	0,	0,  0,	1,	0.58, 9.99,
		-0.09, -0.09375,	0,	0,  0,	1,	0.41, 0.41,
		0.09, -0.09375,	0,	0,  0,	1,	0.58, 0.41,

		-0.09, 0.09375,	0,	0,  0,	1,	0.41,	0.58,
		0.09, 0.09375,	0,	0,  0,	1,	0.58,	0.58,
		0.09, -0.09375,	0,	0,  0,	1,	0.58,	0.41,

		0.53, 0.09,	0,	0,  0,	1,	0.99,	0.58,
		0.53, -0.09,	0,	0,  0,	1,	0.99,	0.41,
		0.09, -0.09,	0,	0,  0,	1,	0.58,	0.41,

		-0.09, 0.53,	0,	0,  0,	1,	0.41,	0.99,
		0.09, 0.53,	0,	0,  0,	1,	0.58,	0.99,
		0.09, 0.09,	0,	0,  0,	1,	0.58,	0.58,

		-0.53, -0.09,	0,	0,  0,	1,	9.99,	0.41,
		-0.53, 0.09,	0,	0,  0,	1,	9.99,	0.58,
		-0.09, 0.09,	0,	0,  0,	1,	0.41,	0.58,

		0.09, -0.53,	0,	0,  0,	1,	0.58,	9.99,
		-0.09, -0.53,	0,	0,  0,	1,	0.41,	1.00,
		-0.09, -0.09,	0,	0,  0,	1,	0.41,	0.41,

	};

	unsigned int indices[] = {
		2, 1, 0,
		5, 4, 3,
		8, 7, 6,
		11, 10, 9,
		14, 13, 12,
		17, 16, 15,
		20, 19, 18,
		23, 22, 21,
		26, 25, 24,
		29, 28, 27 
	};

	glGenVertexArrays(1, &kipasVAO);
	glGenBuffers(1, &kipasVBO);
	glGenBuffers(1, &kipasEBO);

	glBindVertexArray(kipasVAO);

	glBindBuffer(GL_ARRAY_BUFFER, kipasVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kipasEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawKipas(float x, float y, float z, float deg, int rotX, int rotY, int rotZ) {
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texKipasID);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);



	//GLint flatTex = glGetUniformLocation(this->tshaderProgram, "flatTex");
	//glUniform1f(flatTex, 0.0f);

	glBindVertexArray(kipasVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, (glm::mediump_float)deg, glm::vec3(rotX, rotY, rotZ));
	model = glm::scale(model, (glm::vec3(0.5, 0.5, 0.5)));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void Demo::BuildTexturedCube()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &ttexture);
	glBindTexture(GL_TEXTURE_2D, ttexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate_diffusemap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("crate_specularmap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {

		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		0.5, -0.5, 0.5, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		0.5,  0.5, 0.5, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 -0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 -0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 -0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 -0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		-0.5, 0.5, 0.5, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.5, 0.5, -0.5, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		0.5, -0.5, -0.5, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		0.5, -0.5,  0.5, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &tVAO);
	glGenBuffers(1, &tVBO);
	glGenBuffers(1, &tEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildLantai()
{
	glGenTextures(1, &lantaiTexture);
	glBindTexture(GL_TEXTURE_2D, lantaiTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Lantai.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		2.0, 0.0, 2.2, 1.4, 1.9, 0.0, 1.0, 0.0,
		-2.0, 0.0, - 2.2, -0.7, - 0.9, 0.0, 1.0, 0.0,
		-2.0, 0.0, 2.2, 1.4, - 0.9, 0.0, 1.0, 0.0,

		2.0, 0.0, 2.2, 1.4, 1.9, 0.0, 1.0, 0.0,
		2.0, 0.0, - 2.2, -0.7, 1.9, 0.0, 1.0, 0.0,
		-2.0, 0.0, -2.2, -0.7, -0.9, 0.0, 1.0, 0.0,
	};

	unsigned int indices[] = {
		0,  1,  2, 
		3,  4,  5
	};

	glGenVertexArrays(1, &lantaiVAO);
	glGenBuffers(1, &lantaiVBO);
	glGenBuffers(1, &lantaiEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(lantaiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lantaiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lantaiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildtembok()
{
	glGenTextures(1, &tembokTexture);
	glBindTexture(GL_TEXTURE_2D, tembokTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("Tembok001.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		-2.0, 2.0, - 2.2, 1.0, 0.0, 0.0, 0.0, 1.0,
		2.0, 0.0, - 2.2, 0.0, 1.0, 0.0, 0.0, 1.0,
		2.0, 2.0, -2.2, 0.0, 0.0, 0.0, 0.0, 1.0,

		-2.0, 0.0, -2.2, 0.0, 0.6, 1.0, 0.0, 0.0,
		-2.0, 2.0, 2.2, 0.9, - 0.0, 1.0, 0.0, 0.0,
		-2.0, 0.0, 2.2,0.9, 0.6,1.0, 0.0, 0.0,

		2.0, 2.0, -2.2, 0.0, 0.6, -1.0, 0.0, 0.0,
		2.0, 0.0, 2.2, 0.9, 0.0, -1.0, 0.0, 0.0,
		2.0, 2.0, 2.2,0.9, 0.6, -1.0, 0.0, 0.0,

		2.0, 2.0, 2.2, 1.0, 0.0, 0.0, 0.0, -1.0,
		-2.0, 0.0, 2.2, 0.0, 1.0, 0.0, 0.0, -1.0,
		-2.0, 2.0, 2.2, 0.0, 0.0, 0.0, 0.0, -1.0,

		-2.0, 2.0, -2.2, 1.0, 0.0, 0.0, 0.0, 1.0,
		-2.0, 0.0, -2.2, 1.0, 1.0, 0.0, 0.0, 1.0,
		2.0, 0.0, -2.2, 0.0, 0.0, 0.0, 0.0, 1.0,

		-2.0, 0.0, -2.2, 0.0, 0.6, 1.0, 0.0, 0.0,
		-2.0, 2.0, -2.2, 0.0, -0.0, 1.0, 0.0, 0.0,
		-2.0, 2.0, 2.2, 0.9, -0.0, 1.0, 0.0, 0.0,

		2.0, 2.0, -2.2, 0.0, 0.6, -1.0, 0.0, 0.0,
		2.0, 0.0, -2.2, 0.0, 0.0, -1.0, 0.0, 0.0,
		2.0, 0.0, 2.2, 0.9, 0.0, -1.0, 0.0, 0.0,

		2.0, 2.0, 2.2, 1.0, 0.0, 0.0, 0.0, -1.0,
		2.0, 0.0, 2.2, 1.0, 1.0, 0.0, 0.0, -1.0,
		-2.0, 0.0, 2.2,	0.0, 1.0, 0.0, 0.0, -1.0,
		
	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,

	};

	glGenVertexArrays(1, &tembokVAO);
	glGenBuffers(1, &tembokVBO);
	glGenBuffers(1, &tembokEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tembokVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tembokVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tembokEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildwindow()
{
	glGenTextures(1, &windowTexture);
	glBindTexture(GL_TEXTURE_2D, windowTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("window.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		0.4, 1.4, -2.1, 1.0, 0.0, 0.0, 0.0, 1.0,
		-0.4, 0.6, -2.1, 0.0, 1.0, 0.0, 0.0, 1.0,
		0.4, 0.6, -2.1, 0.0, 0.0, 0.0, 0.0, 1.0,

		0.4, 1.4, -2.1, 1.0, 0.0, 0.0, 0.0, 1.0,
		-0.4, 1.4, -2.1, 1.0, 1.0, 0.0, 0.0, 1.0,
		-0.4, 0.6, -2.1, 0.0, 1.0, 0.0, 0.0, 1.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,

	};

	glGenVertexArrays(1, &windowVAO);
	glGenBuffers(1, &windowVBO);
	glGenBuffers(1, &windowEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(windowVAO);

	glBindBuffer(GL_ARRAY_BUFFER, windowVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, windowEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildkakimeja1()
{
	glGenTextures(1, &kakimeja1Texture);
	glBindTexture(GL_TEXTURE_2D, kakimeja1Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		-1.7, 0.6, 0.66, 1.0, 0.0, -1.0, 0.0, 0.0,
		-1.7, -0.01, 0.66, 0.0, 0.0, -1.0, 0.0, 0.0,
		-1.7, -0.01, 0.73, 0.0, 1.0, -1.0, 0.0, 0.0,

		-1.7, 0.6, 0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.7, -0.01, 0.73, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.0, -0.01, 0.73, 0.0, 1.0, 0.0, 0.0, 1.0,

		-1.0, 0.6, 0.73, 1.0, 0.0, 1.0, 0.0, 0.0, 
		-1.0, -0.01, 0.73, 0.0, 0.0, 1.0, 0.0, 0.0,
		-1.0, -0.01, 0.66, 0.0, 1.0, 1.0, 0.0, 0.0,

		-1.0, 0.6, 0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.0, -0.01, 0.66, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.7, -0.01, 0.66, 0.0, 1.0, 0.0, 0.0, -1.0,

		-1.0, -0.01, 0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.01, 0.73, 0.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.01, 0.66, 0.0, 1.0,  0.0, -1.0, 0.0,

		-1.7, 0.6, 0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, 0.73, 0.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, 0.66, 0.0, 1.0, 0.0, 1.0, 0.0,

		-1.7, 0.6, 0.66, 1.0, 0.0, -1.0, 0.0, 0.0,
		-1.7, -0.01, 0.73, 0.0, 1.0, -1.0, 0.0, 0.0,
		-1.7, 0.6, 0.73, 1.0, 1.0, -1.0, 0.0, 0.0,

		-1.7, 0.6, 0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.0, -0.01, 0.73, 0.0, 1.0, 0.0, 0.0, 1.0,
		-1.0, 0.6, 0.73, 1.0, 1.0, 0.0, 0.0, 1.0,

		-1.0, 0.6, 0.73, 1.0, 0.0, 1.0, 0.0, 0.0,
		-1.0, -0.01, 0.66, 0.0, 1.0, 1.0, 0.0, 0.0,
		-1.0, 0.6, 0.66, 1.0, 1.0, 1.0, 0.0, 0.0,

		-1.0, 0.6, 0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.7, -0.01, 0.66, 0.0, 1.0, 0.0, 0.0, -1.0,
		-1.7, 0.6, 0.66, 1.0, 1.0, 0.0, 0.0, -1.0,

		-1.0, -0.01, 0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.01, 0.66, 0.0, 1.0, 0.0, -1.0, 0.0,
		-1.0, -0.01, 0.66, 1.0, 1.0, 0.0, -1.0, 0.0,

		-1.7, 0.6, 0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, 0.66, 0.0, 1.0, 0.0, 1.0, 0.0,
		-1.7, 0.6, 0.66, 1.0, 1.0, 0.0, 1.0, 0.0,

			 
};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &kakimeja1VAO);
	glGenBuffers(1, &kakimeja1VBO);
	glGenBuffers(1, &kakimeja1EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(kakimeja1VAO);

	glBindBuffer(GL_ARRAY_BUFFER, kakimeja1VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kakimeja1EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildkakimeja2()
{
	glGenTextures(1, &kakimeja2Texture);
	glBindTexture(GL_TEXTURE_2D, kakimeja2Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		-1.7, 0.6, -0.7, 1.0, 0.0, -1.0, 0.0, 0.0,
		-1.7, -0.0, -0.7, 0.0, 0.0,	-1.0, 0.0, 0.0,
		-1.7, -0.0, -0.6, 0.0, 1.0, -1.0, 0.0, 0.0,

		-1.7, 0.6, -0.6, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.7, -0.0, -0.6, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.0, -0.0, -0.6, 0.0, 1.0, 0.0, 0.0, 1.0,

		-1.0, 0.6, -0.6, 1.0, 0.0, 1.0, 0.0, 0.0,
		-1.0, -0.0, -0.6, 0.0, 0.0, 1.0, 0.0, 0.0,
		-1.0, -0.0, -0.7, 0.0, 1.0, 1.0, 0.0, 0.0,

		-1.0, 0.6, -0.7, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.0, -0.0, -0.7, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.7, -0.0, -0.7, 0.0, 1.0, 0.0, 0.0, -1.0,

		-1.0, -0.0, -0.6, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.0, -0.6, 0.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.0, -0.7, 0.0, 1.0, 0.0, -1.0, 0.0,

		-1.7, 0.6, -0.6, 1.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, -0.6, 0.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, -0.7, 0.0, 1.0, 0.0, 1.0, 0.0,

		-1.7, 0.6, -0.7, 1.0, 0.0, -1.0, 0.0, 0.0,
		-1.7, -0.0, -0.6, -0.0, -0.6, -1.0, 0.0, 0.0,
		-1.7, 0.6, -0.6, 1.0, 1.0, -1.0, 0.0, 0.0,

		-1.7, 0.6, -0.6, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.0, -0.0, -0.6, 0.0, 1.0, 0.0, 0.0, 1.0,
		-1.0, 0.6, -0.6, 1.0, 1.0, 0.0, 0.0, 1.0,

		-1.0, 0.6, -0.6, 1.0, 0.0, 1.0, 0.0, 0.0,
		-1.0, -0.0, -0.7, 0.0, 1.0, 1.0, 0.0, 0.0,
		-1.0, 0.6, -0.7, 1.0, 1.0, 1.0, 0.0, 0.0,

		-1.0, 0.6, -0.7, 1.0, 0.0, 0.0, 0.0, -1.0, 
		-1.7, -0.0, -0.7, 0.0, 1.0, 0.0, 0.0, -1.0,
		-1.7, 0.6, -0.7, 1.0, 1.0, 0.0, 0.0, -1.0,

		-1.0, -0.0, -0.6, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.7, -0.0, -0.7, 0.0, 1.0, 0.0, -1.0, 0.0,
		-1.0, -0.0, -0.7, 1.0, 1.0, 0.0, -1.0, 0.0,

		-1.7, 0.6, -0.6, 1.0, 0.0, 0.0, 1.0, 0.0,
		-1.0, 0.6, -0.7, 0.0, 1.0, 0.0, 1.0, 0.0,
		-1.7, 0.6, -0.7, 1.0, 1.0, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &kakimeja2VAO);
	glGenBuffers(1, &kakimeja2VBO);
	glGenBuffers(1, &kakimeja2EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(kakimeja2VAO);

	glBindBuffer(GL_ARRAY_BUFFER, kakimeja2VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kakimeja2EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildmeja()
{
	glGenTextures(1, &mejaTexture);
	glBindTexture(GL_TEXTURE_2D, mejaTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left  
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &mejaVAO);
	glGenBuffers(1, &mejaVBO);
	glGenBuffers(1, &mejaEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(mejaVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mejaVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mejaEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);*/

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildtvsup()
{
	glGenTextures(1, &tvsupTexture);
	glBindTexture(GL_TEXTURE_2D, tvsupTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		-1.2, 0.7, 0.1, 0.0, 1.0, 1.0, 0.0, 0.0,
		-1.2, 0.6, -0.1, 1.0, 0.0, 1.0, 0.0, 0.0,
		-1.2, 0.7, -0.1, 0.0, 0.0, 1.0, 0.0, 0.0,

		-1.5, 0.7, 0.1, 0.0, 1.0, 0.0, 0.0, 1.0,
		-1.2, 0.6, 0.1, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.2, 0.7, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0,

		-1.5, 0.7, -0.1, 0.0, 1.0, -1.0, 0.0, 0.0,
		-1.5, 0.6, 0.1, 1.0, 0.0, -1.0, 0.0, 0.0,
		-1.5, 0.7, 0.1, 0.0, 0.0, -1.0, 0.0, 0.0,

		-1.2, 0.7, -0.1, 0.0, 1.0, 0.0, 0.0, -1.0,
		-1.5, 0.6, -0.1, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.5, 0.7, -0.1, 0.0, 0.0, 0.0, 0.0, -1.0,

		-1.5, 0.6, -0.1, 0.0, 1.0, 0.0, -1.0, 0.0,
		-1.2, 0.6, 0.1, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.5, 0.6, 0.1, 0.0, 0.0, 0.0, -1.0, 0.0,

		-1.3, 0.7, -0.0, 0.2, 0.5, 0.6, 0.7, 0.0,
		-1.3, 0.7, 0.0, 0.0, 0.0, 0.6, 0.7, 0.0,
		-1.3, 0.7, -0.0, 0.0, 0.9, 0.6, 0.7, 0.0,

		-1.4, 0.7, 0.0, 0.3, 0.4, -0.6, 0.7, 0.0,
		-1.4, 0.7, -0.0, 0.5, 0.9, -0.6, 0.7, 0.0,
		-1.4, 0.7, 0.0, 0.5, 0.0, -0.6, 0.7, 0.0,

		-1.3, 0.7, 0.0, 0.2, 0.3, 0.0, 0.7, 0.6,
		-1.4, 0.7, 0.0, 0.5, 0.0, 0.0, 0.7, 0.6,
		-1.3, 0.7, 0.0, 0.0, 0.0, 0.0, 0.7, 0.6,

		-1.4, 0.7, -0.0, 0.3, 0.5, 0.0, 0.7, -0.6,
		-1.3, 0.7, -0.0, 0.0, 0.9, 0.0, 0.7, -0.6,
		-1.4, 0.7, -0.0, 0.5, 0.9, 0.0, 0.7, -0.6,

		-1.2, 0.7, -0.1, 0.0, 1.0, 0.0, 1.0, 0.0, 
		-1.5, 0.7, 0.1, 1.0, 0.0, 0.0, 1.0, 0.0,
		-1.2, 0.7, 0.1, 0.0, 0.0, 0.0, 1.0, 0.0,

		-1.4, 0.7, 0.0, 0.3, 0.4, 0.0, 1.0, 0.0,
		-1.3, 0.7, -0.0, 0.2, 0.5, 0.0, 1.0, 0.0,
		-1.4, 0.7, -0.0, 0.3, 0.5, 0.0, 1.0, 0.0,

		-1.2, 0.7, 0.1, 0.0, 1.0, 1.0, 0.0, 0.0,
		-1.2, 0.6, 0.1, 1.0, 1.0, 1.0, 0.0, 0.0,
		-1.2, 0.6, -0.1, 1.0, 0.0, 1.0, 0.0, 0.0,

		-1.5, 0.7, 0.1, 0.0, 1.0, 0.0, 0.0, 1.0,
		-1.5, 0.6, 0.1, 1.0, 1.0, 0.0, 0.0, 1.0,
		-1.2, 0.6, 0.1, 1.0, 0.0, 0.0, 0.0, 1.0,

		-1.5, 0.7, -0.1, 0.0, 1.0, -1.0, 0.0, 0.0,
		-1.5, 0.6, -0.1, 1.0, 1.0, -1.0, 0.0, 0.0,
		-1.5, 0.6, 0.1, 1.0, 0.0, -1.0, 0.0, 0.0,

		-1.2, 0.7, -0.1, 0.0, 1.0, 0.0, 0.0, -1.0,
		-1.2, 0.6, -0.1, 1.0, 1.0, 0.0, 0.0, -1.0,
		-1.5, 0.6, -0.1, 1.0, 0.0, 0.0, 0.0, -1.0,

		-1.5, 0.6, -0.1, 0.0, 1.0, 0.0, -1.0, 0.0,
		-1.2, 0.6, -0.1, 1.0, 1.0, 0.0, -1.0, 0.0,
		-1.2, 0.6, 0.1, 1.0, 0.0, 0.0, -1.0, 0.0,

		-1.3, 0.7, -0.0, 0.2, 0.5, 0.6, 0.7, 0.0,
		-1.3, 0.7, 0.0, 0.2, 0.3, 0.6, 0.7, 0.0,
		-1.3, 0.7, 0.0, 0.0, 0.0, 0.6, 0.7, 0.0,

		-1.4, 0.7, 0.0, 0.3, 0.4, -0.6, 0.7, 0.0,
		-1.4, 0.7, -0.0, 0.3, 0.5, -0.6, 0.7, 0.0,
		-1.4, 0.7, -0.0, 0.5, 0.9, -0.6, 0.7, 0.0,

		-1.3, 0.7, 0.0, 0.2, 0.3, 0.0, 0.7, 0.6,
		-1.4, 0.7, 0.0, 0.3, 0.4, 0.0, 0.7, 0.6,
		-1.4, 0.7, 0.0, 0.5, 0.0, 0.0, 0.7, 0.6,

		-1.4, 0.7, -0.0, 0.3, 0.5, 0.0, 0.7, -0.6,
		-1.3, 0.7, -0.0, 0.2, 0.5, 0.0, 0.7, -0.6,
		-1.3, 0.7, -0.0, 0.0, 0.9, 0.0, 0.7, -0.6,

		-1.2, 0.7, -0.1, 0.0, 1.0, 0.0, 1.0, 0.0,
		-1.5, 0.7, -0.1, 1.0, 1.0, 0.0, 1.0, 0.0,
		-1.5, 0.7, 0.1, 1.0, 0.0, 0.0, 1.0, 0.0,

		-1.4, 0.7, 0.0, 0.3, 0.4, 0.0, 1.0, 0.0, 
		-1.3, 0.7, 0.0, 0.2, 0.3, 0.0, 1.0, 0.0,
		-1.3, 0.7, -0.0, 0.2, 0.5, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,
		36, 37, 38,
		39, 40, 41,
		42, 43, 44, 
		45, 46, 47,
		48, 49, 50,
		51, 52, 53,
		54, 55, 56,
		57, 58, 59,
		60, 61, 62,
		63, 64, 65,

	};

	glGenVertexArrays(1, &tvsupVAO);
	glGenBuffers(1, &tvsupVBO);
	glGenBuffers(1, &tvsupEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tvsupVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tvsupVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tvsupEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::Buildtv()
{
	glGenTextures(1, &tvTexture);
	glBindTexture(GL_TEXTURE_2D, tvTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tv.png", &width, &height, 0, SOIL_LOAD_RGBA);
	if (power == false) {
		unsigned char* image = SOIL_load_image(textureOff, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (power == true) {
		if (channel == 0) {
			unsigned char* image = SOIL_load_image(textureOn, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (channel == 1) {
			unsigned char* image = SOIL_load_image(textureOn1, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (channel == 2) {
			unsigned char* image = SOIL_load_image(textureOn2, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		if (channel == 3) {
			unsigned char* image = SOIL_load_image(textureOn3, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
	}
	
	float vertices[] = {
		// format position, tex coords, normal
		-1.43, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 0.72, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.23, 0.72, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,

		-1.23, 1.18, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,

		-1.43, 0.72, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,

		-1.43, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,

		-1.23, 0.72, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 0.72, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 1.18, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,

		-1.23, 0.72, -0.58, 0.0, 1.0, 0.0, 0.0,  0.0,//
		-1.23, 0.72, 0.58,  1.0, 1.0, 0.0, 0.0,  0.0,
		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 0.0,  0.0,

		-1.43, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,
		-1.23, 0.72, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.23, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,

		-1.23, 1.18, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,
		-1.23, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,

		-1.43, 0.72, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 0.0,
		-1.43, 1.18, 0.58,  0.0, 0.0, 0.0, 0.0, 0.0,

		-1.43, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0, 
		-1.43, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,

		-1.23, 0.72, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 1.18, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.23, 1.18, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,

		-1.23, 0.72, -0.58, 0.0, 1.0, 0.0, 0.0,  0.0,//
		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 0.0,  0.0,
		-1.23, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0,  0.0,

		
	};

	/*float vertices[] = {
		// format position, tex coords, normal
		-1.43, 0.72, -0.58, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.43, 0.72, 0.58,  0.0,0.0, 0.0, -1.0, 0.0,
		-1.23, 0.72, 0.58,  0.0, 1.0, 0.0, -1.0, 0.0,

		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 1.0, 0.0,
		-1.43, 1.18, 0.58,  0.0, 0.0, 0.0, 1.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 1.0, 0.0, 1.0, 0.0,

		-1.43, 0.72, 0.58,  1.0, 0.0, -1.0, 0.0, 0.0,
		-1.43, 0.72, -0.58, 0.0, 0.0, -1.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 1.0, -1.0, 0.0, 0.0,

		-1.43, 0.72, -0.58, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 0.72, -0.58, 0.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 1.18, -0.58, 0.0, 1.0, 0.0, 0.0, 1.0,

		-1.23, 0.72, 0.58, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 0.72, 0.58, 0.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 1.18, 0.58, 0.0, 1.0, 0.0, 0.0, -1.0,

		-1.23, 0.72, -0.58, 0.0, 1.0, 0.0, 0.0,  0.0,//
		-1.23, 0.72, 0.58,  1.0, 1.0, 0.0, 0.0,  0.0,
		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 0.0,  0.0,

		-1.43, 0.72, -0.58, 1.0, 0.0, 0.0, -1.0, 0.0,
		-1.23, 0.72, 0.58,  0.0, 1.0, 0.0, -1.0, 0.0,
		-1.23, 0.72, -0.58, 1.0, 1.0, 0.0, -1.0, 0.0,

		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 1.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 1.0, 0.0, 1.0, 0.0,
		-1.23, 1.18, -0.58, 1.0, 1.0, 0.0, 1.0, 0.0,

		-1.43, 0.72, 0.58,  1.0, 0.0, -1.0, 0.0, 0.0,
		-1.43, 1.18, -0.58, 0.0, 1.0, -1.0, 0.0, 0.0,
		-1.43, 1.18, 0.58,  1.0, 1.0, -1.0, 0.0, 0.0,

		-1.43, 0.72, -0.58, 1.0, 0.0, 0.0, 0.0, 1.0,
		-1.23, 1.18, -0.58, 0.0, 1.0, 0.0, 0.0, 1.0,
		-1.43, 1.18, -0.58, 1.0, 1.0, 0.0, 0.0, 1.0,

		-1.23, 0.72, 0.58, 1.0, 0.0, 0.0, 0.0, -1.0,
		-1.43, 1.18, 0.58, 0.0, 1.0, 0.0, 0.0, -1.0,
		-1.23, 1.18, 0.58, 1.0, 1.0, 0.0, 0.0, -1.0,

		-1.23, 0.72, -0.58, 0.0, 1.0, 0.0, 0.0,  0.0,//
		-1.23, 1.18, 0.58,  1.0, 0.0, 0.0, 0.0,  0.0,
		-1.23, 1.18, -0.58, 0.0, 0.0, 0.0, 0.0,  0.0,


	};*/

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &tvVAO);
	glGenBuffers(1, &tvVBO);
	glGenBuffers(1, &tvEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tvVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tvVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tvEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildTexturedPlane()
{
	// Load and create a texture 
	glGenTextures(1, &ttexture2);
	glBindTexture(GL_TEXTURE_2D, ttexture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("marble_diffusemap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture2);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("marble_specularmap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0, 0.0f,  1.0f,  0.0f,
		50.0, -0.5, -50.0, 50,  0, 0.0f,  1.0f,  0.0f,
		50.0, -0.5,  50.0, 50, 50, 0.0f,  1.0f,  0.0f,
		-50.0, -0.5,  50.0,  0, 50, 0.0f,  1.0f,  0.0f,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &tVAO2);
	glGenBuffers(1, &tVBO2);
	glGenBuffers(1, &tEBO2);

	glBindVertexArray(tVAO2);

	glBindBuffer(GL_ARRAY_BUFFER, tVBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::Buildsofa()
{
	glGenTextures(1, &sofaTexture);
	glBindTexture(GL_TEXTURE_2D, sofaTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		1.7,  0.9,   -0.66, 1.0, 0.0, -1.0, 0.0, 0.0,//
		1.7, -0.01, -0.66, 0.0, 0.0, -1.0, 0.0, 0.0,//
		1.7, -0.01,  0.73, 0.0, 1.0, -1.0, 0.0, 0.0,

		1.7,  0.9,	 0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.7, -0.01,  0.73, 0.0, 0.0, 0.0, 0.0, 1.0,
		1.6, -0.01, 0.73, 0.0, 1.0, 0.0, 0.0, 1.0,

		1.6,  0.9,   0.73, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.6, -0.01, 0.73, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.6, -0.01, -0.66, 0.0, 1.0, 1.0, 0.0, 0.0,

		1.6,  0.9,   -0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.6, -0.01, -0.66, 0.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01, -0.66, 0.0, 1.0, 0.0, 0.0, -1.0,

		1.6, -0.01, 0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01, 0.73, 0.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01, -0.66, 0.0, 1.0,  0.0, -1.0, 0.0,

		1.7, 0.9, 0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.6, 0.9, 0.73, 0.0, 0.0, 0.0, 1.0, 0.0,
		1.6, 0.9, -0.66, 0.0, 1.0, 0.0, 1.0, 0.0,

		1.7, 0.9,   -0.66, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01, 0.73, 0.0, 1.0, -1.0, 0.0, 0.0,
		1.7, 0.9,   0.73, 1.0, 1.0, -1.0, 0.0, 0.0,

		1.7, 0.9,   0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.6, -0.01, 0.73, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.6, 0.9,   0.73, 1.0, 1.0, 0.0, 0.0, 1.0,

		1.6, 0.9,   0.73, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.6, -0.01, -0.66, 0.0, 1.0, 1.0, 0.0, 0.0,
		1.6, 0.9,   -0.66, 1.0, 1.0, 1.0, 0.0, 0.0,

		1.6, 0.9,   -0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01, -0.66, 0.0, 1.0, 0.0, 0.0, -1.0,
		1.7, 0.9,   -0.66, 1.0, 1.0, 0.0, 0.0, -1.0,

		1.6, -0.01, 0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01, -0.66, 0.0, 1.0, 0.0, -1.0, 0.0,
		1.6, -0.01, -0.66, 1.0, 1.0, 0.0, -1.0, 0.0,

		1.7, 0.9, 0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.6, 0.9, -0.66, 0.0, 1.0, 0.0, 1.0, 0.0,
		1.7, 0.9, -0.66, 1.0, 1.0, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &sofaVAO);
	glGenBuffers(1, &sofaVBO);
	glGenBuffers(1, &sofaEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(sofaVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sofaVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sofaEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildsofaBwh()
{
	glGenTextures(1, &sofaBwhTexture);
	glBindTexture(GL_TEXTURE_2D, sofaBwhTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		//X		Z		Y
		1.6,  0.4,   -0.66, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.6, -0.01,  -0.66, 0.0, 0.0, -1.0, 0.0, 0.0,
		1.6, -0.01,   0.73, 0.0, 1.0, -1.0, 0.0, 0.0,

		1.6,  0.4, 	  0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.6, -0.01,   0.73, 0.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,   0.73, 0.0, 1.0, 0.0, 0.0, 1.0,

		1.0,  0.4,    0.73, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,	  0.73, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,  -0.66, 0.0, 1.0, 1.0, 0.0, 0.0,

		1.0,  0.4,   -0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.0, -0.01,  -0.66, 0.0, 0.0, 0.0, 0.0, -1.0,
		1.6, -0.01,  -0.66, 0.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,   0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.6, -0.01,   0.73, 0.0, 0.0, 0.0, -1.0, 0.0,
		1.6, -0.01,  -0.66, 0.0, 1.0,  0.0, -1.0, 0.0,

		1.6, 0.4,     0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.4,     0.73, 0.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.4,    -0.66, 0.0, 1.0, 0.0, 1.0, 0.0,

		1.6, 0.4,   -0.66, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.6, -0.01,  0.73, 0.0, 1.0, -1.0, 0.0, 0.0,
		1.6, 0.3,    0.73, 1.0, 1.0, -1.0, 0.0, 0.0,

		1.6, 0.4,    0.73, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,  0.73, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, 0.4,    0.73, 1.0, 1.0, 0.0, 0.0, 1.0,

		1.0, 0.4,    0.73, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01, -0.66, 0.0, 1.0, 1.0, 0.0, 0.0,
		1.0, 0.4,   -0.66, 1.0, 1.0, 1.0, 0.0, 0.0,

		1.0, 0.4,   -0.66, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.6, -0.01, -0.66, 0.0, 1.0, 0.0, 0.0, -1.0,
		1.6, 0.4,   -0.66, 1.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,  0.73, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.6, -0.01, -0.66, 0.0, 1.0, 0.0, -1.0, 0.0,
		1.0, -0.01, -0.66, 1.0, 1.0, 0.0, -1.0, 0.0,

		1.6, 0.4,    0.73, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.4,   -0.66, 0.0, 1.0, 0.0, 1.0, 0.0,
		1.6, 0.4,   -0.66, 1.0, 1.0, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &sofaBwhVAO);
	glGenBuffers(1, &sofaBwhVBO);
	glGenBuffers(1, &sofaBwhEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(sofaBwhVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sofaBwhVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sofaBwhEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildsofaKiri()
{
	glGenTextures(1, &sofaKiriTexture);
	glBindTexture(GL_TEXTURE_2D, sofaKiriTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		//X		Z		Y
		1.7,  0.6,    0.73, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,   0.73, 0.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,   0.93, 0.0, 1.0, -1.0, 0.0, 0.0,

		1.7,  0.6, 	  0.93, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.7, -0.01,   0.93, 0.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,   0.93, 0.0, 1.0, 0.0, 0.0, 1.0,

		1.0,  0.6,    0.93, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,	  0.93, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,   0.73, 0.0, 1.0, 1.0, 0.0, 0.0,

		1.0,  0.6,    0.73, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.0, -0.01,   0.73, 0.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01,   0.73, 0.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,   0.93, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,   0.93, 0.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,   0.73, 0.0, 1.0,  0.0, -1.0, 0.0,

		1.7, 0.6,     0.93, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,     0.93, 0.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,     0.73, 0.0, 1.0, 0.0, 1.0, 0.0,

		1.7, 0.6,    0.73, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,  0.93, 0.0, 1.0, -1.0, 0.0, 0.0,
		1.7, 0.6,    0.93, 1.0, 1.0, -1.0, 0.0, 0.0,

		1.7, 0.6,    0.93, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,  0.93, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, 0.6,    0.93, 1.0, 1.0, 0.0, 0.0, 1.0,

		1.0, 0.6,    0.93, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,  0.73, 0.0, 1.0, 1.0, 0.0, 0.0,
		1.0, 0.6,    0.73, 1.0, 1.0, 1.0, 0.0, 0.0,

		1.0, 0.6,    0.73, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01,  0.73, 0.0, 1.0, 0.0, 0.0, -1.0,
		1.7, 0.6,    0.73, 1.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,  0.93, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,  0.73, 0.0, 1.0, 0.0, -1.0, 0.0,
		1.0, -0.01,  0.73, 1.0, 1.0, 0.0, -1.0, 0.0,

		1.7, 0.6,    0.93, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,    0.73, 0.0, 1.0, 0.0, 1.0, 0.0,
		1.7, 0.6,    0.73, 1.0, 1.0, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &sofaKiriVAO);
	glGenBuffers(1, &sofaKiriVBO);
	glGenBuffers(1, &sofaKiriEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(sofaKiriVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sofaKiriVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sofaKiriEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::BuildsofaKanan()
{
	glGenTextures(1, &sofaKananTexture);
	glBindTexture(GL_TEXTURE_2D, sofaKananTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("meja.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords, normal
		//X		Z		Y
		1.7,  0.6,    -0.86, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,   -0.86, 0.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,   -0.66, 0.0, 1.0, -1.0, 0.0, 0.0,

		1.7,  0.6, 	  -0.66, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.7, -0.01,   -0.66, 0.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,   -0.66, 0.0, 1.0, 0.0, 0.0, 1.0,

		1.0,  0.6,    -0.66, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,	  -0.66, 0.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,   -0.86, 0.0, 1.0, 1.0, 0.0, 0.0,

		1.0,  0.6,    -0.86, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.0, -0.01,   -0.86, 0.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01,   -0.86, 0.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,   -0.66, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,   -0.66, 0.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,   -0.86, 0.0, 1.0,  0.0, -1.0, 0.0,

		1.7, 0.6,     -0.66, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,     -0.66, 0.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,     -0.86, 0.0, 1.0, 0.0, 1.0, 0.0,

		1.7, 0.6,    -0.86, 1.0, 0.0, -1.0, 0.0, 0.0,
		1.7, -0.01,  -0.66, 0.0, 1.0, -1.0, 0.0, 0.0,
		1.7, 0.6,    -0.66, 1.0, 1.0, -1.0, 0.0, 0.0,

		1.7, 0.6,    -0.66, 1.0, 0.0, 0.0, 0.0, 1.0,
		1.0, -0.01,  -0.66, 0.0, 1.0, 0.0, 0.0, 1.0,
		1.0, 0.6,    -0.66, 1.0, 1.0, 0.0, 0.0, 1.0,

		1.0, 0.6,    -0.66, 1.0, 0.0, 1.0, 0.0, 0.0,
		1.0, -0.01,  -0.86, 0.0, 1.0, 1.0, 0.0, 0.0,
		1.0, 0.6,    -0.86, 1.0, 1.0, 1.0, 0.0, 0.0,

		1.0, 0.6,    -0.86, 1.0, 0.0, 0.0, 0.0, -1.0,
		1.7, -0.01,  -0.86, 0.0, 1.0, 0.0, 0.0, -1.0,
		1.7, 0.6,    -0.86, 1.0, 1.0, 0.0, 0.0, -1.0,

		1.0, -0.01,  -0.66, 1.0, 0.0, 0.0, -1.0, 0.0,
		1.7, -0.01,  -0.86, 0.0, 1.0, 0.0, -1.0, 0.0,
		1.0, -0.01,  -0.86, 1.0, 1.0, 0.0, -1.0, 0.0,

		1.7, 0.6,    -0.66, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.6,    -0.86, 0.0, 1.0, 0.0, 1.0, 0.0,
		1.7, 0.6,    -0.86, 1.0, 1.0, 0.0, 1.0, 0.0,

	};

	unsigned int indices[] = {
		0,  1,  2,
		3,  4,  5,
		6,	7,	8,
		9,	10,	11,
		12,	13,	14,
		15,	16,	17,
		18,	19,	20,
		21,	22,	23,
		24,	25,	26,
		27,	28,	29,
		30,	31,	32,
		33,	34,	35,

	};

	glGenVertexArrays(1, &sofaKananVAO);
	glGenBuffers(1, &sofaKananVBO);
	glGenBuffers(1, &sofaKananEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(sofaKananVAO);

	glBindBuffer(GL_ARRAY_BUFFER, sofaKananVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sofaKananEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawTexturedCube()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ttexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(tVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawLantai()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lantaiTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);

	
	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(lantaiVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawtembok()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tembokTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(tembokVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawwindow()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, windowTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.0f);

	glBindVertexArray(windowVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawkakimeja1()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, kakimeja1Texture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(kakimeja1VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawkakimeja2()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, kakimeja2Texture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(kakimeja2VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawmeja()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mejaTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(mejaVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-1.35, 0.61, 0));
	model = glm::rotate(model, angleStayX, glm::vec3(1, 0, 0));
	model = glm::rotate(model, angleStayX, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.5, 0.9, 1));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//jumlah indice
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawsofa()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sofaTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(sofaVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawsofaBwh()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sofaBwhTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(sofaBwhVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawsofaKiri()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sofaKiriTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(sofaKiriVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawsofaKanan()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sofaKananTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(sofaKananVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawtvsup()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tvsupTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(tvsupVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//jumlah indice
	glDrawElements(GL_TRIANGLES, 66, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::Drawtv()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tvTexture);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 0);


	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(tvVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//jumlah indice
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::DrawTexturedPlane()
{
	UseShader(this->tshaderProgram);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, ttexture2);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.diffuse"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, stexture2);
	glUniform1i(glGetUniformLocation(this->tshaderProgram, "material.specular"), 3);

	GLint shininessMatLoc = glGetUniformLocation(this->tshaderProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	glBindVertexArray(tVAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->tshaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Multiple Lighting Demo", 800, 600, false, false);
}