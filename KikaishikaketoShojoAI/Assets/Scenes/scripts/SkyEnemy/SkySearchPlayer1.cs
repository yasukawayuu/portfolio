using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
public class SkySearchPlayer1 : MonoBehaviour
{

    [SerializeField] float len = 6.0f;                           // ���E����

    [SerializeField]
    [Tooltip("�ǂ�������Ώ�")]
    private GameObject player;

    [SerializeField]
    private Text text;

    public bool invaded;                      // ������ɂ��邩�ǂ����̎��ʎq

    [SerializeField]
    [Tooltip("�ǂꂭ�炢���������Ɍ����邩")]
    private float downAngle = -1.0f;

    private Ray centerray;
    private Vector3 colPosition;

    [SerializeField]
    GameObject move;
    [SerializeField]
    GameObject search;
    public AudioClip seMove;
    AudioSource audioSourceMove;
    public AudioClip seSearch;
    AudioSource audioSourceSearch;
    // Start is called before the first frame update
    void Start()
    {
        text.enabled = false;
        audioSourceMove = move.GetComponent<AudioSource>();
        audioSourceSearch = search.GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (audioSourceMove.isPlaying == false)
            {
                audioSourceMove.PlayOneShot(seMove);
            }
            //�T���͈͂̒��S
            //�����ʒu�̌��������킹��
            Vector3 dir = new Vector3(0, downAngle, 0) + transform.forward;
            //�����ʒu�@�p�x�w��
            centerray = new Ray(transform.position, dir);
            RaycastHit centerhit;
            if (Physics.Raycast(centerray, out centerhit))
            {
                colPosition = centerhit.point;
            }
            //Ray�̉���
            //�J�n�ʒu�A�����~�����������܂ł̋����A�F
            Debug.DrawRay(centerray.origin, centerray.direction * centerhit.distance, Color.red);

            //�T���͈͂̒��S�𗘗p���ĉ~�̓����蔻��
            //Y���𖳎�����X����Z���Ŕ���
            float l;
            Vector3 col = colPosition;
            l = Mathf.Sqrt(Mathf.Pow(player.transform.position.x - col.x, 2)
                + Mathf.Pow(player.transform.position.z - col.z, 2));

            if (l < len)
            {
                //�͈͓��ɓ������v���C���[�֌�������Ray���΂�
                //�����ʒu�p�x�w��
                if (invaded == false)
                {
                    //    invaded = true;
                    //    text.enabled = true;
                    // Player�̈ʒu���擾
                    Vector3 dirct = player.transform.position;
                    Ray ray = new Ray(transform.position, (dirct - transform.position));
                    RaycastHit hit;
                    if (Physics.Raycast(ray, out hit))
                    {
                        if (hit.collider.name != "Player")
                        {
                        }
                        else
                        {
                            invaded = true;
                            text.enabled = true;
                        }
                    }
                    //Ray�̉���
                    //�J�n�ʒu�A�����~�����������܂ł̋����A�F
                    Debug.DrawRay(ray.origin, ray.direction * 10, new Color(1.0f, 1.0f, 0.0f, 1.0f), 0.1f, true);
                }
            }

            // ���F���Ă���ꍇ����p���L����
            if (invaded == true)
            {
                colPosition = transform.position;

                if (audioSourceSearch.isPlaying == false)
                {
                    audioSourceSearch.PlayOneShot(seSearch);
                }
            }
            else// if(searchAngle != searchAnglefalse)
            {
                colPosition = centerhit.point;
            }
        }
        else
        {
            audioSourceMove.Stop();
            audioSourceSearch.Stop();
        }
    }
        public void Search()
        {
            invaded = false;
            text.enabled = false;
        }

        private void OnCollisionEnter(Collision collision)
        {
            if (collision.gameObject.CompareTag("Player"))
            {
                invaded = false;
                text.enabled = false;
                audioSourceSearch.Stop();
            }
        }

#if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        Handles.color = new Color(1.0f, 0, 0, 0.1f);
        Handles.DrawSolidDisc(colPosition, new Vector3(0,0.1f,0), len);
    }
#endif
}