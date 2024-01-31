//
// Mecanim�̃A�j���[�V�����f�[�^���A���_�ňړ����Ȃ��ꍇ�� Rigidbody�t���R���g���[��
// �T���v��
// 2014/03/13 N.Kobyasahi
// 2015/03/11 Revised for Unity5 (only)
//
using UnityEngine;
using System.Collections;

namespace Player
{
    // �K�v�ȃR���|�[�l���g�̗�L
    [RequireComponent(typeof(Animator))]
    [RequireComponent(typeof(CapsuleCollider))]
    [RequireComponent(typeof(Rigidbody))]

    public class P_C : MonoBehaviour
    {
        [Tooltip("�L�����N�^�[�̃X�s�[�h")]
        private float speed;
        [Tooltip("�L�����N�^�[�̒ʏ펞�X�s�[�h")]
        public float walkspeed = 0.1f;
        [Tooltip("�L�����N�^�[�̃A�C�e���擾���X�s�[�h")]
        public float slowspeed = 0.07f;

        public float animSpeed = 1.5f;              // �A�j���[�V�����Đ����x�ݒ�
        public float lookSmoother = 3.0f;           // a smoothing setting for camera motion
        public bool useCurves = true;               // Mecanim�ŃJ�[�u�������g�����ݒ肷��
                                                    // ���̃X�C�b�`�������Ă��Ȃ��ƃJ�[�u�͎g���Ȃ�
        public float useCurvesHeight = 0.5f;        // �J�[�u�␳�̗L�������i�n�ʂ����蔲���₷�����ɂ͑傫������j

        // �L�����N�^�[�R���g���[���i�J�v�Z���R���C�_�j�̎Q��
        private CapsuleCollider col;
        private Rigidbody rb;
        // �L�����N�^�[�R���g���[���i�J�v�Z���R���C�_�j�̈ړ���
        private Vector3 velocity;
        // �L�����N�^�[��PlayerController���擾
        private PlayerController pc;

        // CapsuleCollider�Őݒ肳��Ă���R���C�_��Heiht�ACenter�̏����l�����߂�ϐ�
        private float orgColHight;
        private Vector3 orgVectColCenter;
        private Animator anim;                          // �L�����ɃA�^�b�`�����A�j���[�^�[�ւ̎Q��

        [SerializeField]
        private bool running;

        // ������
        void Start()
        {
            // Animator�R���|�[�l���g���擾����
            anim = GetComponent<Animator>();
            // CapsuleCollider�R���|�[�l���g���擾����i�J�v�Z���^�R���W�����j
            col = GetComponent<CapsuleCollider>();
            rb = GetComponent<Rigidbody>();
            // CapsuleCollider�R���|�[�l���g��Height�ACenter�̏����l��ۑ�����
            orgColHight = col.height;
            orgVectColCenter = col.center;

            // �L�����N�^�[��PlayerController���擾
            pc = GetComponent<PlayerController>();

            // �X�s�[�h������������
            speed = walkspeed;
        }


        // �ȉ��A���C������.���W�b�h�{�f�B�Ɨ��߂�̂ŁAFixedUpdate���ŏ������s��.
        void FixedUpdate()
        {
            float moveHorizontal = Input.GetAxis("Horizontal");             // ���̓f�o�C�X�̐�������h�Œ�`
            float moveVertical = Input.GetAxis("Vertical");             // ���̓f�o�C�X�̐�������v�Œ�`                          

            rb.useGravity = true;//�W�����v���ɏd�͂�؂�̂ŁA����ȊO�͏d�͂̉e�����󂯂�悤�ɂ���


            // �ȉ��A�L�����N�^�[�̈ړ�����
            // �L�����N�^�[�̃X�s�[�h����
            SetCharacterSpeed();

            velocity = new Vector3(moveHorizontal, 0, moveVertical);

            /*
            // �A�j���[�V�����̏���
            if (velocity.magnitude > 0.1f)
            {
                running = true;
                anim.SetBool("run", running);
                //anim.SetBool("hiku", true);
                Vector3 cameraForward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1)).normalized;
                Vector3 moveForward = cameraForward * moveVertical + Camera.main.transform.right * moveHorizontal;

                transform.rotation = Quaternion.LookRotation(moveForward);

                transform.Translate(Vector3.forward * speed);
            }
            else
            {
                running = false;
                anim.SetBool("run", running);
               
            }

            if (velocity.magnitude > 0.1f&&Input.GetKey(KeyCode.Z))
            {
                
                //anim.SetBool("run", running);
                anim.SetBool("hiku", true);
                Vector3 cameraForward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1)).normalized;
                Vector3 moveForward = cameraForward * moveVertical + Camera.main.transform.right * moveHorizontal;

                transform.rotation = Quaternion.LookRotation(moveForward);

                transform.Translate(Vector3.forward * speed *-0.5f) ;
            }
            else
            {
                running = false;
                //anim.SetBool("run", running);
                anim.SetBool("hiku", running);
            }

            if (Input.GetKey(KeyCode.Space))
            {
                anim.SetBool("jump", true);
            }
            AnimatorStateInfo state = anim.GetCurrentAnimatorStateInfo(0);
            if (state.IsName("tobu"))
            {
                anim.SetBool("jump", false);
            }

            if (Input.GetKey(KeyCode.Z))
            {
                anim.SetBool("hiku_start", true);
            }
            AnimatorStateInfo state2 = anim.GetCurrentAnimatorStateInfo(0);
            if (state2.IsName("hiku_start"))
            {
                anim.SetBool("hiku_start", false);
            }
            */
        }

        // �L�����N�^�[�̃R���C�_�[�T�C�Y�̃��Z�b�g�֐�
        void resetCollider()
        {
            // �R���|�[�l���g��Height�ACenter�̏����l��߂�
            col.height = orgColHight;
            col.center = orgVectColCenter;
        }

        // �L�����N�^�[�̈ړ����x��ݒ�
        void SetCharacterSpeed()
        {
            if (!pc.GetItem()) speed = walkspeed;
            else speed = slowspeed;
        }
    }
}