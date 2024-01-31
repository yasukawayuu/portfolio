using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class PearTalk
{
    private int m_no;
    private string m_words;

    public PearTalk(int no, string words)
    {
        m_no = no;
        m_words = words;
    }

    public int GetNo()
    {
        return m_no;
    }
    public string GetWords()
    {
        return m_words;
    }
}
public class Talk1 : MonoBehaviour
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
        words.Add(new PearTalk(1, "ア,イ,！,大,丈,夫,？,無,事,！,？"));
        words.Add(new PearTalk(0, "う,ん"));
        words.Add(new PearTalk(1, "よ,か,っ,た,ぁ,、,助,け,に,来,る,の,に,時,間,か,か,っ,ち,ゃ,っ,た,か,ら,、,心,配,し,て,た,ん,だ,。"));
        words.Add(new PearTalk(1, "エ,ス,の,目,を,か,い,く,ぐ,っ,て,牢,屋,の,カ,ギ,を,ハ,ッ,キ,ン,グ,す,る,の,に,１,週,間,も,か,か,っ,た,よ,…,…,。"));
        words.Add(new PearTalk(1, "と,に,か,く,今,開,け,る,か,ら,ね,！"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "メイト";
        Count = 0;
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if(next == true)
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

            if (words.Count == Count)
            {
                goal.NextStage();
            }
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
