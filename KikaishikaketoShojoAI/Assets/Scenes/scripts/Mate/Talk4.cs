using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;


public class Talk4 : MonoBehaviour
{
    [SerializeField] Text nametext;
    [SerializeField] Text talktext;
    [SerializeField] Canvas canvas;
    private string[] wordArray;
    private List<PearTalk> words;
    private int Count;

    public bool talkFlag;

    public int num = 0;
    public int cnt = 0;

    public AudioClip se;
    AudioSource audioSource;

    bool next = true;
    void Start()
    {
        words = new List<PearTalk>();
        words.Add(new PearTalk(1, "��,��,��,��,��,��,��,��,��,��,��,��,�B"));
        words.Add(new PearTalk(1, "��,��,��,��,��,��,��,��,��,�A,��,��,�c,��,��,��,��,��,��,��,��,��,�H"));
        words.Add(new PearTalk(1, "��,��,��,��,��,�O,��,�o,��,��,��,��,��,�A,��,��,��,��,�C,��,��,��,��,��,�s,��,��,�B"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "���C�g";
        Count = 0;
        talkFlag = false;
        Count = 0;
        audioSource = GetComponent<AudioSource>();
    }
    
    void Update()
    {

        if (next == true)
        {
            if (Input.GetMouseButtonDown(0) || Input.GetKeyDown("joystick button 2"))
            {
                if (words[Count].GetNo() == 0)
                {
                    nametext.text = "�A�C";
                }
                else
                {
                    nametext.text = "���C�g";
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
            gameObject.GetComponent<CutSceneController>().cutSceneState = CUTSCENE.CUTSCENE_ENDING;
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
