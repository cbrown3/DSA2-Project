#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if(bModifier)
		fSpeed *= 10.0f;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);
#pragma endregion

#pragma region Model Positioning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_m4Model = m_m4Model * glm::translate(vector3(-0.1f, 0.0f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_m4Model = m_m4Model * glm::translate(vector3(0.1f, 0.0f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_m4Model = m_m4Model * glm::translate(vector3(0.0f, 0.1f, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_m4Model = m_m4Model * glm::translate(vector3(0.0f,-0.1f, 0.0f));
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOZ));
	ON_KEY_PRESS_RELEASE(F3, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F4, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOX));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, bLeft = true, NULL)
	if (bLeft)
	{
		//m_m4Camera = m_pCameraMngr->GetCameraSpace(); //Space of the camera
		//m_m4Camera = m_pCameraMngr->GetCameraSpaceAdjusted(); //Space right in front of the camera
		m_m4Camera = m_pCameraMngr->GetCameraPlane(); //Space right in front of the camera forming a plane that covers the window

		POINT pt;
		GetCursorPos(&pt);
		m_v3ClickedOn = m_pCameraMngr->GetClickOnWorldSpace(static_cast<int>(pt.x), static_cast<int>(pt.y));
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
