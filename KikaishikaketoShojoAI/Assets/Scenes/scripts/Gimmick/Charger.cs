using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Charger : MonoBehaviour
{

    [SerializeField]
    [Tooltip("ボタンに接続")]
    GimmickButton[] button;
    
    [SerializeField]
    [Tooltip("視覚的に分かりやすく")]
    ChargeCnt[] chargeobj;
    
    [SerializeField]
    [Tooltip("最大までの時間")]
    private int charge_time = 0;

    private int energy_charge = 0;
    private int charge_cnt = 0;
    private float time = 0.0f;

    public bool active = false;


    public AudioClip se;
    AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        energy_charge = 0;
        charge_cnt = 0;
        time = 0.0f;
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.timeScale > 0)
        {
            if (active == false)
            {
                time += Time.deltaTime;

                if (time > 1.0f)
                {
                    for (int i = 0; i < button.Length; i++)
                    {

                        if (button[i].active == true)
                        {
                            energy_charge += 1;
                        }
                    }

                    if (energy_charge > charge_time / chargeobj.Length)
                    {
                        energy_charge = -charge_time / chargeobj.Length;
                        chargeobj[charge_cnt].ChangeColor();
                        charge_cnt += 1;
                    }

                    if (charge_cnt >= chargeobj.Length)
                    {
                        active = true;
                        audioSource.PlayOneShot(se);
                    }
                    time = 0f;
                }
            }
        }
    }
}
