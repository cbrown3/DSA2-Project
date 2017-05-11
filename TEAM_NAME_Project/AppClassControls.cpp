#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;


#pragma region ON_KEY_PRESS_RELEASE
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false, bLastF = false, bLastTab = false, bLastI = false, bLastO =false,
				bLastSpace = false, bLastBackSpace = false;
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

#pragma region Joshua_McMahan_Additions_April_30th_TEST_COMMANDS
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_v3Position = vector3(-0.01f, 0.0f, 0.0f); //Needs to be named that apparantly? 
		Player.RigidTrans(m_v3Position); //This way it acts as a constant acceleration. Will tweak later for actual stuff
		//Player.RigidRotate(m_v3Position);
		//m_pCameraMngr->MoveSideways(Player.rigidBody.state.velocity.x); // camera will follow t Player instead of static movement
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_v3Position = vector3(0.01f, 0.0f, 0.0f); //Needs to be named that apparantly?
		Player.RigidTrans(m_v3Position); //This way it acts as a constant acceleration. Will tweak later for actual stuff
		//Player.RigidRotate(m_v3Position);
		//m_pCameraMngr->MoveSideways(Player.rigidBody.state.velocity.x); // camera will follow t Player instead of static movement

	}
	//if the camera is orthographic, move in the negative z axis, if not, move in the positive y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!bModifier)
		{
			m_v3Position = vector3(0.0f, 0.0f, -0.01f); //Needs to be named that apparantly?
			Player.RigidTrans(m_v3Position); //This way it acts as a constant acceleration. Will tweak later for actual stuff
			//m_pCameraMngr->SetPosition(m_pCameraMngr->GetPosition() + Player.rigidBody.state.velocity, -1);// camera will follow t Player instead of static movement

		}
		else
		{
			m_v3Position = vector3(0.0f, 0.01f, 0.0f); //Needs to be named that apparantly?
			Player.RigidTrans(m_v3Position); //This way it acts as a constant acceleration. Will tweak later for actual stuff

			//m_pCameraMngr->MoveVertical(Player.rigidBody.state.velocity.y);

		}
	}
	//if the camera is orthographic, move in the positive z axis, if not, move in the negative y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!bModifier)
		{
			m_v3Position = vector3(0.0f, 0.0f, 0.01f); //Needs to be named that apparantly?
			Player.RigidTrans(m_v3Position); //This way it acts as a constant acceleration. Will tweak later for actual stuff
			//Player.RigidRotate(m_v3Position);
			//m_pCameraMngr->SetPosition(m_pCameraMngr->GetPosition() + Player.rigidBody.state.velocity, -1);// camera will follow t Player instead of static movement

		}
		else
		{
			//logic for stopping movement downward, for the ground
			if (Player.GetPosition().y < 0)
			{
				Player.RigidTrans(vector3(0.0f, 0.01f, 0.0f));

				//m_pCameraMngr->MoveVertical(Player.rigidBody.state.velocity.y);

			}
			else
			{
				Player.RigidTrans(vector3(0.0f, -0.01f, 0.0f));

				//m_pCameraMngr->MoveVertical(Player.rigidBody.state.velocity.y);

			}
		}
	}
#pragma endregion


#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));

#pragma endregion

#pragma region Load Models

	//cycle models on tab
	ON_KEY_PRESS_RELEASE(Tab, NULL, CycleModels());

	//if you press Space, it will load in a random model
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		m_pBoundingObjectMngr->AddObject()
	}*/

#pragma endregion

#pragma region Switch Colliding Boxes
	ON_KEY_PRESS_RELEASE(I, NULL, {
	if (renderBox)
		{
			renderBox = false;
		}
		else
		{
			renderBox = true;
		}

	});

	ON_KEY_PRESS_RELEASE(O, NULL, {

		if (renderAlligned)
		{
			renderAlligned = false;
		}
		else
		{
			renderAlligned = true;
		}

	});

	ON_KEY_PRESS_RELEASE(Space, NULL, SpawnModel( vector3(rand() % 10 - 5, 0, rand() % 10 - 5)) );

	ON_KEY_PRESS_RELEASE(BackSpace, NULL, ClearModels());

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
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
	if (bLeft)
	{
		//Turn off the visibility of all BOs for all instances
		m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
		//Get the Position and direction of the click on the screen
		std::pair<vector3, vector3> pair =
			m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		float fDistance = 0;//Stores the distance to the first colliding object
		m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

		//If there is a collision
		if (m_selection.first >= 0)
		{
			//Turn on the BO of the group
			m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

			//Turn of the BO of the instance but not the group
			m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
		}
	}
	
	//added functionality to rotate with the r button for those without a middle mouse button
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)|| sf::Keyboard::isKeyPressed(sf::Keyboard::R) )
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
