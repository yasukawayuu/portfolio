
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "mainCamera.h"
#include "transform.h"
#include "player.h"
#include "scene.h"
#include "input.h"
#include "cursor.h"

void MainCamera::Init()
{
	m_Transform->Position = D3DXVECTOR3(0.0f, 3.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

}


void MainCamera::Update()
{

	Scene *scene = Manager::GetInstance()->GetScene();
	Player *player = scene->GetGameObject<Player>();
	
	if (scene->GetGameObject<Player>())
	{
		Transform* playerpos = player->GetComponent<Transform>();
		//ファーストパーソンビュー
		m_Transform->Position = playerpos->Position + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
		m_Target = m_Transform->Position + playerpos->GetForward() + D3DXVECTOR3(0.0f, Cursor::GetCursorPosition().y, 0.0f);
	}



	//トップビュー
	/*m_Target = player->GetPosition();
	m_Transform->Position = m_Target + D3DXVECTOR3(0.0f, 3.0f, -5.0f);*/

	//サードパーソンビュー
	//m_Target = playerpos->Position + playerpos->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	//m_Transform->Position = m_Target - playerpos->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	

	if (Input::GetKeyTrigger('C'))
	{
		m_ShakeAmplitude = 0.05f;
	}


	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.3f;
}

void MainCamera::Draw()
{
	Renderer* renderer = renderer->GetInstance();

	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_Transform->Position + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);

	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	renderer->SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	renderer->SetProjectionMatrix(&m_ProjectionMatrix);
	
}

bool MainCamera::CheckView(D3DXVECTOR3 Position,float Size)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);
	
	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Transform->Position;

	//左面判定
	{
		v1 = wpos[0] - m_Transform->Position;
		v2 = wpos[2] - m_Transform->Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n,&n);

		if (D3DXVec3Dot(&n, &v) < -Size)
			return false;
	}

	//右面判定
	{
		v1 = wpos[3] - m_Transform->Position;
		v2 = wpos[1] - m_Transform->Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Size)
			return false;
	}

	//上面判定
	{
		v1 = wpos[1] - m_Transform->Position;
		v2 = wpos[0] - m_Transform->Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Size)
			return false;
	}

	//下面判定
	{
		v1 = wpos[2] - m_Transform->Position;
		v2 = wpos[3] - m_Transform->Position;
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -Size)
			return false;
	}

	{
		/*D3DXVECTOR3 forward = GetForward();
		D3DXVec3Normalize(&forward, &forward);

		if (D3DXVec3Dot(&forward, &v) < 0.0f)
			return false;*/
	}

	return true;
}

