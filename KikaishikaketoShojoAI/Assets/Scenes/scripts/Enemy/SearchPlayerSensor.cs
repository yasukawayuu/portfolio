using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.UI;

public class SearchPlayerSensor : MonoBehaviour
{
    [SerializeField] float searchAngle = 60f;                // ����p
    [SerializeField] int len = 14;                           // ���E����
    [SerializeField] private float searchAngletrue = 180f;    // ���F���Ă���Ƃ��̎���p
    float searchAnglefalse;                                  // ���F���Ă��Ȃ��Ƃ��̎���p

    [SerializeField]
    [Tooltip("�ǂ�������Ώ�")]
    private GameObject player;

    [SerializeField]
    private Text text;

    private Ray ray;

    private Vector3 positionDiff;             // ���g�i�G�j�ƃv���C���[�̋����x�N�g��
    public bool invaded;                      // ������ɂ��邩�ǂ����̎��ʎq

    //�Z���T�[
    [SerializeField]
    Alarm alarm;

    [SerializeField]
    GameObject walk;
    [SerializeField]
    GameObject search;
    public AudioClip seWalk;
    AudioSource audioSourceWalk;
    public AudioClip seSearch;
    AudioSource audioSourceSearch;

    private Vector3 oldPos;
    void Start()
    {
        searchAnglefalse = searchAngle;

        // Ray�𐶐�
        ray = new Ray(transform.position, (player.transform.position - transform.position));
        audioSourceWalk = walk.GetComponent<AudioSource>();
        audioSourceSearch = search.GetComponent<AudioSource>();
        oldPos = transform.position;
    }

    void Update()
    {

        if (Time.timeScale > 0)
        {
            positionDiff = player.transform.position - transform.position;  // ���g�i�G�j�ƃv���C���[�̋���
            var angle = Vector3.Angle(transform.forward, positionDiff);  // �G��Z���@�Ɓ@�G�ƃv���C���[�̃x�N�g���̊p�x�����

            // ���F���Ă��邩�ǂ���
            if ((positionDiff.magnitude <= len && angle <= searchAngle) && (player.GetComponent<PlayerController>().isHidden == false))
            {
                RaycastHit hit; // �Փ˂����I�u�W�F�N�g
                ray = new Ray(transform.position + (player.transform.position - transform.position) * 0.1f, (player.transform.position - transform.position));
                if (Physics.Raycast(ray, out hit))
                {
                    // �I�u�W�F�N�g��Player���擾����
                    if (hit.collider.gameObject.CompareTag("Player"))
                    {
                        invaded = true;
                        text.enabled = true;
                    }
                }
            }
            else
            {
                invaded = false;
                text.enabled = false;
            }

            // ���F���Ă���ꍇ����p���L����
            if (invaded == true)
            {
                searchAngle = searchAngletrue;

                if (audioSourceSearch.isPlaying == false)
                {
                    audioSourceSearch.PlayOneShot(seSearch);
                }
            }
            else
            {
                searchAngle = searchAnglefalse;
            }


            if (alarm.active == true)
            {
                invaded = true;
                text.enabled = true;
            }


            RaycastHit p; // �Փ˂����I�u�W�F�N�g
            ray = new Ray(transform.position + (player.transform.position - transform.position) * 0.1f, (player.transform.position - transform.position));
            if (Physics.Raycast(ray, out p, 1))
            {
                // �I�u�W�F�N�g��Player���擾����
                if (p.collider.gameObject.CompareTag("Player"))
                {
                    alarm.ResetAlarm();
                    invaded = false;
                    text.enabled = false;
                }
            }


            //�ړ����Ă�����
            if (oldPos.x != transform.position.x || oldPos.z != transform.position.z)
            {
                if (audioSourceWalk.isPlaying == false)
                {
                    audioSourceWalk.PlayOneShot(seWalk);
                }
                oldPos = transform.position;
            }
            else
            {
                audioSourceWalk.Stop();
            }

        }
        else
        {
            audioSourceWalk.Stop();
            audioSourceSearch.Stop();
        }
    }
    
#if UNITY_EDITOR
    private void OnDrawGizmos()
    {
        Handles.color = new Color(1.0f, 0, 0, 0.3f);
        Handles.DrawSolidArc(transform.position, Vector3.up, Quaternion.Euler(0f, -searchAngle, 0f) * transform.forward, searchAngle * 2f, len);
    }
#endif
}
