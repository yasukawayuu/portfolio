using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LaserController : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnParticleCollision(GameObject other)
    {
        //PlayerÉäÉXÉ|Å[Éì
        if (other.gameObject.tag == "Player") other.gameObject.GetComponent<PlayerController>().DeadPlayer();
    }
}
