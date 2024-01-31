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
        words.Add(new PearTalk(1, "��,��,��,��,�x,��,��,�{,��,��,��,��,�H"));
        words.Add(new PearTalk(1, "�x,��,�V,�X,�e,��,��,��,�A,�G,�X,��,�x,�z,��,��,��,��,��,��,�A,��,��,��,��,�S,��,��,��,��,��,��,��,��,��,�v,��,�B"));
        words.Add(new PearTalk(1, "��,��,��,��,��,��,��,��,��,�T,�d,��,�i,��,��,�B"));
        words.Add(new PearTalk(1, "�{,�N,��,��,�w,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "�c,�c,��,��,�A,��,��,��,��,��,��,��,�w,��,��,��,��,��,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "��,��,�e,��,��,��,��,��,��,��,��,��,��,�A,�x,��,��,�{,��,��,��,�A,�C,��,��,��,��,��,��,��,��,��,�A"));
        words.Add(new PearTalk(1, "��,��,��,�e,��,�B,��,��,��,��,�i,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "���C�g";
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
                        nametext.text = "�A�C";
                        break;
                    case 1:
                        nametext.text = "���C�g";
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
