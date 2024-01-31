using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TitleController : MonoBehaviour
{
    public string NextScene;

    public Text Qtext;
    public Text Ptext;
    bool a_flag;
    float a_color;
    // Use this for initialization
    void Start()
    {
        a_flag = false;
        a_color = 0;
    }

    // Update is called once per frame
    void Update()
    {
        //���N���b�N��a_flag��True�ɂ���
        if (Input.GetMouseButtonDown(0))
        {
            a_flag = true;
            a_color = 1;
        }
        //a_flag��true�̊Ԏ��s����
        if (a_flag)
        {
            //�e�L�X�g�̓����x��ύX����
            Qtext.color = new Color(0, 0, 0, a_color);
            Ptext.color = new Color(0, 0, 0, a_color);
            a_color -= Time.deltaTime;
            //�����x��0�ɂȂ�����I������B
            if (a_color < 0)
            {
                a_color = 0;
                a_flag = false;
                SceneManager.LoadScene(NextScene);
            }
        }
    }
}
