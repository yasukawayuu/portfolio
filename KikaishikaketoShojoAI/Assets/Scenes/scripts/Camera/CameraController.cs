    using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour
{
    public GameObject player;  // �ʂ̃I�u�W�F�N�g

    private Vector3 offset;    // �ʂ���J�����܂ł̋���
    private Vector3 nulloffset;

    private int length;        // �傫��

    public float rotateSpeed = 2.0f;            //��]�̑���

    private float titleminus;  // �^�C�g����̕␳
    private bool isCS;         // �J�����������������ǂ���

    private Vector3 Position;
    private RaycastHit Hit;
    private float Distance;
    private int Mask;

    Vector3 PlayerPos;
    //public Material monotone;
    
    Vector3 angle;
    void Start()
    {
        titleminus = -2.0f;
        offset = transform.position - player.transform.position;
        nulloffset = new Vector3(0, 0, 0);
        isCS = true;
        PlayerPos = player.transform.position;
        Position = transform.localPosition;
        Distance = Vector3.Distance(player.transform.position, transform.position);
        Mask = ~(1 << LayerMask.NameToLayer("Player"));
    }

    void LateUpdate()
    {
        // ��������
        if (isCS == true) CameraSetting();

        //�J�����ړ�
        if (player != null) transform.position += player.transform.position - PlayerPos;
        PlayerPos = player.transform.position;

        var controllerNames = Input.GetJoystickNames();

        Vector3 angle = new Vector3(Input.GetAxis("Mouse X") * rotateSpeed, Input.GetAxis("Mouse Y") * rotateSpeed, 0);

        if (Input.GetAxis("RightStickX") > 0.01 || Input.GetAxis("RightStickY") > 0.01
            || Input.GetAxis("RightStickX") < -0.01 || Input.GetAxis("RightStickY") < -0.01)
        {
            angle = new Vector3(Input.GetAxis("RightStickX") * rotateSpeed * 0.6f, Input.GetAxis("RightStickY") * rotateSpeed, 0);
        }



        Vector3 orbitOrigin = player.transform.position;
        transform.RotateAround(orbitOrigin, Vector3.up, angle.x);
        //�J�����Փˏ���
        //CameraCollisionCheck();
    }

    //�J�����̏�������
    void CameraSetting()
    {
        if (titleminus <= 0)
        {
            //this.transform.position -= new Vector3(0, 0, titleminus - (titleminus - 0.01f));
            //titleminus += 0.005f;
            //if (player.activeInHierarchy == true) player.SetActive(false);
        }
        else if (player.activeInHierarchy == false)
        {
            player.SetActive(true);
            isCS = false;
        }
    }

    void CameraCollisionCheck()
    {
        if (Physics.SphereCast(PlayerPos, 0.3f, (transform.position - PlayerPos).normalized, out Hit, 10.0f, Mask))
        {
            transform.position = PlayerPos + (transform.position - PlayerPos).normalized * Hit.distance;
        }
        else
        {
            transform.localPosition = Vector3.Lerp(transform.localPosition, Position, 1);
        }
    }
}