using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    Rigidbody rb;
    [SerializeField] private float JumpPower;

    [SerializeField] private bool isGround;    // �n�ʂɑ������Ă��邩�ǂ���
    public bool isHidden;                      // �B��Ă��邩�ǂ���

   public  Vector3 playerRespawnPos;                  // �v���C���[�̃��X�|�[�����W
    Vector3 playerangle;

    private GameObject Cube;                   // �����Ă���I�u�W�F�N�g���

    private float rayDistance = 1.0f;

    [SerializeField] private GameObject target;
    private GameObject camera;
    private CameraController cameraController;

    private Vector3 CameraPotision;

    [SerializeField]
    GameObject walk;
    [SerializeField]
    GameObject jump;

    public AudioClip seWalk;
    public AudioClip seJump;
    AudioSource audioSourceWalk;
    AudioSource audioSourceJump;


    private Vector3 oldPos;

    Animator anim;

    [SerializeField]
    Resporn res;

    float plPos = 0.0f;

    [SerializeField]
    bool respornPos = false;

    [SerializeField]
    Vector3 rpos;
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        camera = GameObject.Find("Main Camera");
        cameraController = camera.GetComponent<CameraController>();
        Cube = null;
        isGround = true;
        playerRespawnPos = gameObject.transform.position;
        playerangle = transform.eulerAngles;
        rayDistance = 1.0f;
        //CameraPotision = new Vector3(-44.92f,13.57f,-6.12f);


        audioSourceWalk = walk.GetComponent<AudioSource>();
        audioSourceJump = jump.GetComponent<AudioSource>();

        oldPos = transform.position;

        anim = GetComponent<Animator>();


        if (respornPos == true)
        {
            SetRespawnPos(rpos);
        }

    }

    void Update()
    {
        if (Time.timeScale > 0 && res.dead == false && res.start == false)
        {
            Debug.DrawRay(transform.position, transform.forward * rayDistance, Color.red, 0.1f);


            // �擾����Item�������[�X�����Ƃ���Cube��null�ɂ���

            // �W�����v
            if ((Input.GetKeyDown("space") || Input.GetKeyDown("joystick button 1")) && isGround)
            {
                // �A�C�e�������������Ă��Ȃ��ꍇ�̂�
                if (Cube == null)
                {
                    Debug.Log("�W�����v����");
                    isGround = false;
                    rb.AddForce(0.0f, JumpPower, 0.0f, ForceMode.Impulse);
                    anim.SetBool("jump", true);
                }
            }

            if (Cube != null)
            {
                audioSourceWalk.Stop();
                anim.SetBool("osu", true);
            }

            Vector3 velocity = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            if (velocity.magnitude != 0)
            {
                anim.SetBool("run", true);
                if (audioSourceWalk.isPlaying == false)
                {
                    audioSourceWalk.PlayOneShot(seWalk);
                }
            }
            else
            {
                anim.SetBool("run", false);
                audioSourceWalk.Stop();

            }

            if(isGround == false)
            {
                audioSourceWalk.Stop();
            }
        }
        else
        {
            if(Time.deltaTime == 0)
            {
                audioSourceWalk.Stop();
                audioSourceJump.Stop();
            }
        }
    }

    private void LateUpdate()
    {
        if(res.start == true)
        {
            PlayerRespawn();

            rb.freezeRotation = true;
            res.ReStart();
        }
        else
        {
            rb.AddForce(0.0f, -2.0f, 0.0f, ForceMode.Force);
        }
    }

    // Player�����̃I�u�W�F�N�g�ɂԂ��������ɌĂяo�����
    void OnCollisionEnter(Collision other)
    {
        if ((other.gameObject.tag == "Ground") || (other.gameObject.tag == "Item"))
        {
            if(isGround == false)
            {
                audioSourceJump.PlayOneShot(seJump);
            }
            isGround = true;
            anim.SetBool("jump", false);
        }
    }

    // Player�����̃I�u�W�F�N�g���痣�ꂽ���ɌĂяo�����
    private void OnCollisionExit(Collision collision)
    {

    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Enemy")
        {
            DeadPlayer();
            res.PlayerDead();
        }

        if(other.gameObject.tag == "ShadowWall")
        {
            isHidden = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "ShadowWall")
        {
            isHidden = false;
        }
    }

    // �擾�A�C�e���̎󂯓n��
    public GameObject GetItem()
    {
        return Cube;
    }
    public void PlayerRespawn()
    {
        gameObject.SetActive(false);
        gameObject.transform.position = playerRespawnPos;
        transform.eulerAngles = playerangle;
        rb.freezeRotation = true;
        // �����A�C�e���̃��X�|�[��
        SetRespawnItem();
    }
    // ���X�|�[�����W�̍X�V
    public void SetRespawnPos(Vector3 pos)
    {
        playerRespawnPos = pos;
    }

    // �����A�C�e���̃��X�|�[��
    public void SetRespawnItem()
    {
        if(Cube!=null)
        {
            Cube.GetComponent<ItemController>().ResetItem();
            Cube = null;
        }
    }

    public void ItemGet(GameObject item)
    {
        // Cube�Ɏ擾����Item��ۑ�
        Cube = item;
        Cube.gameObject.transform.position = new Vector3(target.transform.position.x, 0.8f, target.transform.position.z);
        Cube.gameObject.transform.SetParent(this.transform);
    }

    public void ReleseItem(GameObject item)
    {
        anim.SetBool("osu", false);
        Cube = null;
    }

    //public Vector3 GetCameraPotision()
    //{
    //    return CameraPotision;
    //}

    public void DeadPlayer()
    {
        rb.freezeRotation = false;
        rb.AddForce(1.0f, 0.0f, 2.0f, ForceMode.Impulse);
        rb.AddTorque(5.0f, 10.0f, 5.0f, ForceMode.Impulse);
        res.PlayerDead();
    }
}