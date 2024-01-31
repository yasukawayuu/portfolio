using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MateTalk// MateTalkクラス
{
    public List<string> Line;        // 通常会話のセリフ
    public int count;     // 会話列数カウント
    public bool canTalk;  // 会話可能かどうか
    public bool isEnd;    // 最期まで会話したかどうか

    public Canvas canvas;            // canvasを取得
    public Text nameText;            // Textを取得
    public Text text;                // Textを取得

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
    public int TalkNum;              // 会話の回数
    public int num = 100;                 // 会話中の番号
    public List<GameObject> TalkField;// 会話が発生する場所

    public List<string> Line0;  // 通常会話のセリフ
    public List<string> Line1;  // 通常会話のセリフ
    public List<string> Line2;  // 通常会話のセリフ
    public List<string> Line3;  // 通常会話のセリフ
    public List<string> Line4;  // 通常会話のセリフ
    public List<string> Line5;  // 通常会話のセリフ
    public List<string> Line6;  // 通常会話のセリフ
    public List<string> Line7;  // 通常会話のセリフ

    public string Name;              // 名前

    public Canvas canvas;            // canvasを取得
    public Text nameText;            // Textを取得
    public Text text;                // Textを取得

    private MateTalk[] mateTalks;            // MateTalkクラス

    void Start()
    {
        mateTalks = new MateTalk[TalkNum];
        for (int i=0;i<TalkNum;i++)
        {
            mateTalks[i] = new MateTalk(canvas, nameText, text); // すべての会話情報を初期化
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
        // 会話が終わっていないとき
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

    // 会話終了
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
            // 範囲内に入ったかどうか
            if (other.gameObject.name== "MateTalk1")
            {
                num = 0;
            }
            else if (other.gameObject.name == "MateTalk2")
            {
                num = 1;
            }

            // 会話可能かどうか
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
    //        // 範囲外に出た時会話出来なくなる
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
