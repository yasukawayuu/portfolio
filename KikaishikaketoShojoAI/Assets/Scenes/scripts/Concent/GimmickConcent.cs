using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GimmickConcent : MonoBehaviour
{
    [SerializeField]
    GameObject concent;
    //�R���Z���g�����������ǂ���
    public bool active = false;

    [SerializeField]
    private bool isPlayer = false;

    float currentTime = 0.0f;
    float countNow = 0.0f;
    public float span = 4.0f;

    Rigidbody rb;
    
    [SerializeField]
    float colMove = 0.3f;
    BoxCollider bc;

    //Rigitbody�œ����Ȃ��悤�ɂ��邽�߂̏����l
    private Vector3 pos;
    private Vector3 rot;

    [SerializeField]
    GameObject move;
    [SerializeField]
    GameObject end;
       

    public AudioClip seMove;
    AudioSource audioSourceMove;
    public AudioClip seEnd;
    AudioSource audioSourceEnd;
    // Start is called before the first frame update
    void Start()
    {
        rb = concent.GetComponent<Rigidbody>();

        pos = concent.transform.position;
        rot = concent.transform.eulerAngles;
        bc = concent.GetComponent<BoxCollider>();
        audioSourceMove = move.GetComponent<AudioSource>();
        audioSourceEnd = end.GetComponent<AudioSource>();
        audioSourceMove.volume = 0.0f;
        countNow = 1.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (active == false)
            {
                if (isPlayer == true)
                {
                    if (Input.GetKey(KeyCode.Z) || Input.GetKey("joystick button 0"))
                    {
                        currentTime += Time.deltaTime;
                    }
                }

                if (currentTime > span)
                {
                    active = true;

                    audioSourceEnd.PlayOneShot(seEnd);
                    //������
                    rb.AddForce(8.0f, 80.0f, 11.0f, ForceMode.Impulse);
                    rb.AddTorque(1.0f, 0.0f, 1.5f, ForceMode.Impulse);
                    //�����蔻��̒���
                    bc.center = new Vector3(bc.center.x, bc.center.y - colMove, bc.center.z);
                }
                else if (countNow < currentTime)
                {
                    if (audioSourceMove.isPlaying == false)
                    {
                        audioSourceMove.PlayOneShot(seMove);
                    }
                    concent.transform.position = new Vector3(concent.transform.position.x,
                        concent.transform.position.y + (0.3f / span) * currentTime, concent.transform.position.z);
                    //������
                    rb.AddForce(0.0f, (currentTime * 0.5f), 0.0f, ForceMode.Impulse);
                    countNow += 1.0f;
                    audioSourceMove.volume += 0.075f;
                }

                //RigitBody�œ����Ȃ�
                concent.transform.position = new Vector3(pos.x, concent.transform.position.y, pos.z);
                concent.transform.eulerAngles = rot;


            }
        }
    }


    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("Target"))
        {
            isPlayer = true;
        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Target"))
        {
            isPlayer = false;
        }
    }
}
