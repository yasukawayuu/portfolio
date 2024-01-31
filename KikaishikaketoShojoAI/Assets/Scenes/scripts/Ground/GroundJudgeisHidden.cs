using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GroundJudgeisHidden : MonoBehaviour
{
    public int groundsplitX = 15; // Ground�̉��̕�����
    public int groundsplitY = 15; // Ground�̏c�̕�����
    public float groundWidth;     // Ground�̉���
    public float groundDepth;     // Ground�̏c��
    public float groundpointWidth;// Ground�̊e�n�_�̉��Ԋu
    public float groundpointDepth;// Ground�̊e�n�_�̏c�Ԋu

    GameObject sun;             // Sun���擾
    GameObject player;          // player���擾

    public GroundInfo[,] groundinfo;   // GroundInfo�̍쐬

    Vector3 origin;             // �����̈ʒu
    Vector3 direction;          // �^�[�Q�b�g�̈ʒu
    Ray ray;                    // Raycast

    //test
    int frame = 0;

    void Start()
    {
        // Sun���擾
        sun = GameObject.Find("Sun");
        // Player���擾
        player = GameObject.Find("Player");

        // Ground�̏����擾
        groundWidth = 3;
        groundDepth = 3;

        // Ground�̊e�n�_�̊Ԋu��ݒ�
        groundpointWidth = groundWidth;
        groundpointDepth = groundDepth;

        // groundinfo�̏�����
        groundinfo = new GroundInfo[groundsplitX, groundsplitY];
        for (int y = 0; y < groundsplitY; y++)
        {
            for (int x = 0; x < groundsplitX; x++)
            {
                groundinfo[x, y].pos
                    = new Vector3((-groundpointWidth * 5) + groundpointWidth * x, 0.0f, (-groundpointDepth * 5) + groundpointDepth * y);
                groundinfo[x, y].posInt = new Vector2Int(x, y);
                groundinfo[x, y].isHidden = true;
                groundinfo[x, y].isUseShadowWall = false;
            }
        }

        // �����ʒu���擾
        origin = new Vector3(0, 0, 0);
        // �����ʒu��ݒ�
        direction = new Vector3(0, 0, 0);
        // Ray�𐶐�
        ray = new Ray(origin, direction);
    }

    void Update()
    {
        // test
        frame++;
        if (frame % 10 == 0)
        {
            for (int y = 0; y < groundsplitY; y++)
            {
                for (int x = 0; x < groundsplitX; x++)
                {
                    groundinfo[x, y].pos.x = player.transform.position.x + (-groundpointWidth * 5) + groundpointWidth * x;
                    groundinfo[x, y].pos.z = player.transform.position.z + (-groundpointDepth * 5) + groundpointDepth * y;
                    groundinfo[x, y].isHidden = true;
                    groundinfo[x, y].isUseShadowWall = false;
                }
            }
        }

        // �����̈ʒu���擾
        origin = sun.transform.position;

        GroundJudge();
    }

    // GroundInfo�̏���ݒ�
    void GroundJudge()
    {
        // Ground�̂��ׂĂ̒n�_���Q�Ƃ���
        for (int y = 0; y < groundsplitY; y++)
        {
            for (int x = 0; x < groundsplitX; x++)
            {
                CalcRaycast(x, y);
                HitCheckRaycast(x, y);
            }
        }
    }

    // Ray�̌������v�Z
    void CalcRaycast(int x, int y)
    {
        // Player�̈ʒu���擾
        direction = groundinfo[x, y].pos;
        // Ray�𐶐�
        ray = new Ray(origin, (direction - origin));
    }

    // Ray�̏Փ˔���
    void HitCheckRaycast(int x, int y)
    {
        RaycastHit hit; // �Փ˂����I�u�W�F�N�g

        // Ray�̏Փ˔���
        if (Physics.Raycast(ray, out hit))
        {
            // �Փ˂����I�u�W�F�N�g�̖��O���擾
            string name = hit.collider.gameObject.tag;
            // �e�ɂ��Ȃ��ꍇ
            if (name == "Ground")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "ShadowWall")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Enemy")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Player")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Respawn")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "NPC")
            {
                groundinfo[x, y].isHidden = false;
            }
            else if (name == "Untagged")
            {
                groundinfo[x, y].isHidden = false;
            }
            // �e�ɂ���ꍇ
            else
            {
                groundinfo[x, y].isHidden = true;
                Debug.DrawRay(origin, (direction - origin), new Color(1.0f, 0.0f, 0.0f, 1.0f), 0.1f, true);
            }
        }

    }
}

// �t�B�[���h�̒n�_�̏��N���X
public struct GroundInfo
{
    public bool isHidden;     // �B��Ă��邩�ǂ���
    public Vector3 pos;       // �n�_�̍��W
    public Vector2Int posInt; // �n�_�̔z��

    public bool isUseShadowWall; // ShadowWall�𐶐����Ă��邩�ǂ���
}