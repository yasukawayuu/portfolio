using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;




public class Talk2 : MonoBehaviour
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
        words.Add(new PearTalk(0, "�G,�X,��,��,?"));
        words.Add(new PearTalk(1, "�P,�T,��,�O,��,��,��,��,��,��,��,��,�N,��,��,��,��,�{,�l,��,��,�B"));
        words.Add(new PearTalk(1, "�c,��,��,�A,�l,��,��,��,��,��,�A,�{,�N,��,��,��,��,��,�m,��,��,��,��,��,A,I,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(0, "��,��,��,��,�H"));
        words.Add(new PearTalk(1, "��,��,��,�A,�A,�C,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,�c,�c,�B"));
        words.Add(new PearTalk(1, "�P,�T,��,�O,�A,��,�m,��,��,��,��,��,��,��,��,�G,�X,��,�A,��,��,��,��,��,��,��,��,��,��,�\,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "��,��,��,��,��,��,�x,��,�V,�X,�e,��,��,��,��,��,��,��,��,�A,��,��,��,��,��,��,��,�E,��,��,��,��,��,��,��,�c,�B"));
        words.Add(new PearTalk(1, "��,��,�c,��,��,��,��,��,��,��,��,��,�A,��,�m,��,�c,�c"));
        words.Add(new PearTalk(0, "��,��,�E,��,��,��,��,��,��,��,��,��,��,�H"));
        words.Add(new PearTalk(1, "�A,�C,��,��,��,��,��,��,�A,�O,��,�o,��,��,��,��,�A,�C,��,��,��,�F,��,��,�K,�v,��,��,��,��,��,�v,��,�B"));
        words.Add(new PearTalk(1, "��,��,��,��,�o,��,��,��,��,��,��,��,��,��,�b,�N,��,��,��,��,��,��,��,�A,��,��,�F,��,��,��,��,�J,��,��,��,��,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "�c,��,��,��,��,�G,�X,��,��,�A,�n,�b,�L,��,�O,��,��,��,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(0, "��,��,��,��,�F,��,�H"));
        words.Add(new PearTalk(1, "��,��,��,�N,��,��,��,��,�A,��,�m,��,��,��,�F,��,��,��,��,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "��,�R,��,��,��,��,��,��,��,��,��,�B,��,��,��,��,��,��,��,��,��,��,��,��,��,�c,�c"));
        words.Add(new PearTalk(1, "�G,�X,��,��,��,��,��,��,��,��,��,��,��,��,��,��,��,�E,�o,��,��,��,�B"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "MATE";
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
