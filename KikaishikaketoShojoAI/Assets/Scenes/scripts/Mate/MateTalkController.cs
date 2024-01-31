using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MateTalk// MateTalk�N���X
{
    public List<string> Line;        // �ʏ��b�̃Z���t
    public int count;     // ��b�񐔃J�E���g
    public bool canTalk;  // ��b�\���ǂ���
    public bool isEnd;    // �Ŋ��܂ŉ�b�������ǂ���

    public Canvas canvas;            // canvas���擾
    public Text nameText;            // Text���擾
    public Text text;                // Text���擾

    public MateTalk(Canvas can, Text na, Text te)
    {
        count = 0;
        canTalk = false;
        isEnd = false;

        canvas = can;
        nameText = na;
        text = te;
    }


}



    public class MateTalkController : MonoBehaviour
{
    public int TalkNum;              // ��b�̉�
    public int num = 100;                 // ��b���̔ԍ�
    public List<GameObject> TalkField;// ��b����������ꏊ

    public List<string> Line0;  // �ʏ��b�̃Z���t
    public List<string> Line1;  // �ʏ��b�̃Z���t
    public List<string> Line2;  // �ʏ��b�̃Z���t
    public List<string> Line3;  // �ʏ��b�̃Z���t
    public List<string> Line4;  // �ʏ��b�̃Z���t
    public List<string> Line5;  // �ʏ��b�̃Z���t
    public List<string> Line6;  // �ʏ��b�̃Z���t
    public List<string> Line7;  // �ʏ��b�̃Z���t

    public string Name;              // ���O

    public Canvas canvas;            // canvas���擾
    public Text nameText;            // Text���擾
    public Text text;                // Text���擾

    private MateTalk[] mateTalks;            // MateTalk�N���X

    void Start()
    {
        mateTalks = new MateTalk[TalkNum];
        for (int i=0;i<TalkNum;i++)
        {
            mateTalks[i] = new MateTalk(canvas, nameText, text); // ���ׂẲ�b����������
            switch (i)
            {
                case 0: mateTalks[i].Line = Line0; break;
                case 1: mateTalks[i].Line = Line1; break;
                case 2: mateTalks[i].Line = Line2; break;
                case 3: mateTalks[i].Line = Line3; break;
                case 4: mateTalks[i].Line = Line4; break;
                case 5: mateTalks[i].Line = Line5; break;
                case 6: mateTalks[i].Line = Line6; break;
                case 7: mateTalks[i].Line = Line7; break;
                default: break;
            }
            
        }
        canvas.enabled = false;
    }


    public void TalkLine()
    {
        // ��b���I����Ă��Ȃ��Ƃ�
        if (!mateTalks[num].isEnd)
        {
            mateTalks[num].count++;
            if (mateTalks[num].count > mateTalks[num].Line.Count - 1)
            {
                mateTalks[num].isEnd = true;
                EndTalk();
            }
            text.text = mateTalks[num].Line[mateTalks[num].count];
        }
    }

    // ��b�I��
    private void EndTalk()
    {
        mateTalks[num].count = 0;
        mateTalks[num].canTalk = false;
        canvas.enabled = false;
        num = 100;
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("MateTalk"))
        {
            // �͈͓��ɓ��������ǂ���
            if (other.gameObject.name== "MateTalk1")
            {
                num = 0;
            }
            else if (other.gameObject.name == "MateTalk2")
            {
                num = 1;
            }

            // ��b�\���ǂ���
            if (!mateTalks[num].isEnd)
            {
                mateTalks[num].canTalk = true;
                canvas.enabled = true;
                mateTalks[num].nameText.text = ("-" + Name + "-");
                if (!mateTalks[num].isEnd) mateTalks[num].text.text = mateTalks[num].Line[0];
            }
        }
    }

    //private void OnTriggerExit(Collider other)
    //{
    //    if (other.gameObject.CompareTag("Player"))
    //    {
    //        // �͈͊O�ɏo������b�o���Ȃ��Ȃ�
    //        count = 0;
    //        canTalk = false;
    //        canvas.enabled = false;
    //    }
    //}

    public bool GetcanTalk()
    {
        return mateTalks[num].canTalk;
    }
}
