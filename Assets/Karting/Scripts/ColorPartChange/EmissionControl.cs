using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class EmissionControl : MonoBehaviour
{
   
   private ParticleSystem pulsePS;
   public float eRate = 1.0f;

   public TMP_Text pText;

   string psVal;

   public float pusleRec;
   string PulseValue;



    void Start()
    {
        pulsePS = GetComponent<ParticleSystem>();
        //StartCoroutine

        // convert float value of pulse to string value
        //  float floatValue1 = float.Parse(stringValue);

    }

    // Update is called once per frame
    void Update()
    {
        psVal = pText.text;
        pusleRec = float.Parse(psVal);

        var emission = pulsePS.emission;
        emission.rateOverTime = eRate; 

//pulse sensor x particle system logic
        if(pusleRec != 0.0){
            eRate = pusleRec / 3;
        }
    }
}
