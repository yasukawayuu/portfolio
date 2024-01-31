using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class NPCTalkController : MonoBehaviour
{
    public string Name;              // 名前
    public List<string> Line;        // 通常会話のセリフ

    public Canvas canvas;            // canvasを取得
    public Text nameText;            // Textを取得
    public Text text;                // Textを取得

    public int count;     // 会話列数カウント

    private bool canTalk; // 会話可能かどうか
    private bool isEnd;   // 最期まで会話したかどうか
    void Start()
    {
        count = 0;
        canTalk = false;
        isEnd = false;
        canvas.enabled = false;
    }

    public void TalkLine()
    {
        // 会話が終わっていないとき
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

    // 会話終了
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
            // 範囲内に入った時会話可能になる
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
            // 範囲外に出た時会話出来なくなる
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
