using UnityEngine;
using UnityEngine.UI;

public class TalkPlayer : MonoBehaviour
{
    private GameObject npc;
    private NPCTalkController npctalk;
    private GameObject mate;
    private MateTalkController matetalk;

    private void Start()
    {
        mate = GameObject.Find("MATE");
        matetalk = mate.GetComponent<MateTalkController>();
    }

    public void Talk()
    {
        if (npc != null)
        {
            npctalk.count++;
            npctalk.TalkLine();
        }

        if (matetalk.num != 100)
        {
            matetalk.TalkLine();
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("NPC") && npc == null)
        {
            npc = other.gameObject;
            npctalk = npc.GetComponent<NPCTalkController>();
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("NPC"))
        {
            npc = null;
            npctalk = null;
        }
    }
}