using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class NPCTalkController : MonoBehaviour
{
    public string Name;              // ���O
    public List<string> Line;        // �ʏ��b�̃Z���t

    public Canvas canvas;            // canvas���擾
    public Text nameText;            // Text���擾
    public Text text;                // Text���擾

    public int count;     // ��b�񐔃J�E���g

    private bool canTalk; // ��b�\���ǂ���
    private bool isEnd;   // �Ŋ��܂ŉ�b�������ǂ���
    void Start()
    {
        count = 0;
        canTalk = false;
        isEnd = false;
        canvas.enabled = false;
    }

    public void TalkLine()
    {
        // ��b���I����Ă��Ȃ��Ƃ�
        if(!isEnd)
        {
            if(count > Line.Count - 1)
            {
                isEnd = true;
                EndTalk();
            }
            text.text = Line[count];
        }
    }

    // ��b�I��
    private void EndTalk()
    {
        count = 0;
        canTalk = false;
        canvas.enabled = false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Player") && !isEnd)
        {
            // �͈͓��ɓ���������b�\�ɂȂ�
            canTalk = true;
            canvas.enabled = true;
            nameText.text = ("-" + Name + "-");
            if(!isEnd) text.text = Line[0];
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            // �͈͊O�ɏo������b�o���Ȃ��Ȃ�
            count = 0;
            canTalk = false;
            canvas.enabled = false;
        }
    }

    public bool GetcanTalk()
    {
        return canTalk;
    }
}
