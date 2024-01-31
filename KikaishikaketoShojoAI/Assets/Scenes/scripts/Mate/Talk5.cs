using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Talk5 : MonoBehaviour
{
    [SerializeField] Text nametext;
    [SerializeField] Text talktext;
    [SerializeField] Canvas canvas;
    private string[] wordArray;
    private List<PearTalk> words;
    private int Count;

    [SerializeField]
    GoalController goal;
    [SerializeField]
    ChangeMt[] change;
    [SerializeField]
    ImageDel imd;


    [SerializeField]
    GameObject damage;
    public AudioClip bossdamage;
    AudioSource audioSourceDamage;

    [SerializeField]
    GameObject end;
    public AudioClip bossend;
    AudioSource audioSourceEnd;

    public int num = 0;
    public int cnt = 0;

    public AudioClip se;
    AudioSource audioSource;

    bool next = true;


    void Start()
    {
        words = new List<PearTalk>();
        words.Add(new PearTalk(0, "��,�A,�A,��,��,�V,��,�c,�c,�c"));
        words.Add(new PearTalk(0, "��,�^,�V,�m,�c,�J,�c,�c,�c,�c,�A,�A,�c,�C,�c,�c"));
        words.Add(new PearTalk(1, "��,��,��,��,�I,��,��,��,��,�c,�A,��,��,�A,��,��,��,��,�o,��,��,!"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "���C�g";
        Count = 0;

        audioSourceDamage = damage.GetComponent<AudioSource>();
        audioSourceEnd = end.GetComponent<AudioSource>();
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
                        nametext.text = "�G�X";
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
        else if (words.Count - 1 == Count)
        {
            for(int i = 0; i < change.Length; i++)
            {
                change[i].ChangeMat();
            }
            imd.ImageFalse();
            audioSourceDamage.Stop();
            audioSourceEnd.PlayOneShot(bossend);
        }
        else
        {
            if(audioSourceDamage.isPlaying == false)
            {
                audioSourceDamage.PlayOneShot(bossdamage);
            }
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
