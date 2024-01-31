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
        words.Add(new PearTalk(0, "エ,ス,っ,て,?"));
        words.Add(new PearTalk(1, "１,週,間,前,の,あ,の,事,件,を,引,き,起,こ,し,た,張,本,人,だ,よ,。"));
        words.Add(new PearTalk(1, "…,ま,あ,、,人,っ,て,い,う,か,、,ボ,ク,と,同,じ,く,博,士,に,造,ら,れ,た,A,I,な,ん,だ,け,ど,ね,。"));
        words.Add(new PearTalk(0, "あ,の,事,件,？"));
        words.Add(new PearTalk(1, "そ,っ,か,、,ア,イ,は,い,き,な,り,捕,ま,っ,ち,ゃ,っ,た,ん,だ,も,ん,ね,…,…,。"));
        words.Add(new PearTalk(1, "１,週,間,前,、,博,士,の,最,高,傑,作,だ,っ,た,エ,ス,が,、,い,き,な,り,自,我,を,持,っ,て,暴,走,し,た,ん,だ,。"));
        words.Add(new PearTalk(1, "こ,の,研,究,所,の,警,備,シ,ス,テ,ム,が,乗,っ,取,ら,れ,て,、,研,究,者,は,み,ん,な,殺,さ,れ,て,し,ま,っ,た,…,。"));
        words.Add(new PearTalk(1, "そ,の,…,言,い,に,く,い,ん,だ,け,ど,、,博,士,も,…,…"));
        words.Add(new PearTalk(0, "私,が,殺,さ,れ,て,い,な,い,の,は,な,ぜ,？"));
        words.Add(new PearTalk(1, "ア,イ,が,無,事,な,の,は,、,外,に,出,る,た,め,に,ア,イ,の,生,体,認,証,が,必,要,だ,か,ら,だ,と,思,う,。"));
        words.Add(new PearTalk(1, "研,究,所,の,出,入,り,口,に,は,強,固,な,ロ,ッ,ク,が,か,か,っ,て,い,て,、,生,体,認,証,で,し,か,開,か,な,い,よ,う,に,な,っ,て,い,る,ん,だ,。"));
        words.Add(new PearTalk(1, "…,さ,す,が,の,エ,ス,で,も,、,ハ,ッ,キ,ン,グ,は,で,き,な,か,っ,た,み,た,い,だ,ね,。"));
        words.Add(new PearTalk(0, "私,の,生,体,認,証,？"));
        words.Add(new PearTalk(1, "事,件,が,起,こ,っ,た,時,、,博,士,が,生,体,認,証,を,書,き,換,え,た,み,た,い,な,ん,だ,。"));
        words.Add(new PearTalk(1, "理,由,は,分,か,ら,な,い,け,ど,ね,。,と,に,か,く,そ,う,い,う,わ,け,だ,か,ら,…,…"));
        words.Add(new PearTalk(1, "エ,ス,に,見,つ,か,ら,な,い,よ,う,に,研,究,所,か,ら,脱,出,し,よ,う,。"));
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
