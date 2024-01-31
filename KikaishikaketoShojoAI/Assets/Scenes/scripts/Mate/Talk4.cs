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
        words.Add(new PearTalk(1, "い,よ,い,よ,次,が,最,後,の,部,屋,だ,。"));
        words.Add(new PearTalk(1, "一,応,聞,い,て,お,く,け,ど,、,や,り,残,し,た,こ,と,は,な,い,よ,ね,？"));
        words.Add(new PearTalk(1, "も,う,少,し,で,外,に,出,ら,れ,る,け,ど,、,最,後,ま,で,気,を,抜,か,ず,に,行,こ,う,。"));
        words.Add(new PearTalk(1, ""));
        nametext.text = "メイト";
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
                    nametext.text = "アイ";
                }
                else
                {
                    nametext.text = "メイト";
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
