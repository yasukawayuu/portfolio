using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Talk3 : MonoBehaviour
{
    [SerializeField] Text nametext;
    [SerializeField] Text talktext;
    [SerializeField] Canvas canvas;
    private string[] wordArray;
    private List<PearTalk> words;
    private int Count;

    [SerializeField]
    GoalController goal;

    public int num = 0;
    public int cnt = 0;

    public AudioClip se;
    AudioSource audioSource;

    bool next = true;
    void Start()
    {
        words = new List<PearTalk>();
        words.Add(new PearTalk(1, "あ,そ,こ,の,警,備,ロ,ボ,が,見,え,る,？"));
        words.Add(new PearTalk(1, "警,備,シ,ス,テ,ム,は,今,、,エ,ス,の,支,配,下,に,あ,る,か,ら,、,捕,ま,る,と,牢,屋,に,戻,さ,れ,ち,ゃ,う,と,思,う,。"));
        words.Add(new PearTalk(1, "見,つ,か,ら,な,い,よ,う,に,慎,重,に,進,も,う,。"));
        words.Add(new PearTalk(1, "ボ,ク,が,光,学,迷,彩,を,か,け,て,あ,げ,る,。"));
        words.Add(new PearTalk(1, "…,…,ま,あ,、,光,に,当,た,る,と,光,学,迷,彩,は,解,け,て,し,ま,う,ん,だ,け,ど,ね,。"));
        words.Add(new PearTalk(1, "で,も,影,の,中,に,入,っ,て,い,る,時,は,、,警,備,ロ,ボ,か,ら,は,ア,イ,が,見,え,な,く,な,る,か,ら,、"));
        words.Add(new PearTalk(1, "う,ま,く,影,に,隠,れ,な,が,ら,進,ん,で,い,こ,う,。"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "メイト";
        Count = 0;
        Count = 0;
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {

        if (next == true)
        {
            if (Input.GetMouseButtonDown(0) || Input.GetKeyDown("joystick button 2"))
            {
                switch (words[Count].GetNo())
                {
                    case 0:
                        nametext.text = "アイ";
                        break;
                    case 1:
                        nametext.text = "メイト";
                        break;
                }

                talktext.text = "";
                canvas.enabled = true;
                string word = words[Count].GetWords();
                num = word.Length;
                wordArray = word.Split(',');
                StartCoroutine("SetText");
                Count++;
                cnt = 0;
                next = false;
            }
        }
            

        if (words.Count == Count)
        {
            goal.NextStage();
        }

        if (Time.timeScale == 0)
        {
            audioSource.Stop();
        }
    }

    IEnumerator SetText()
    {
        foreach (var p in wordArray)
        {
            talktext.text = talktext.text + p;
            yield return new WaitForSeconds(0.1f);

            cnt += 2;
            if (num == cnt - 1)
            {
                audioSource.Stop();
                next = true;
            }
            else
            {
                if (audioSource.isPlaying == false && num != 0)
                {
                    audioSource.Play();
                }
            }
        }
    }
}
