using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class ChangeColor : MonoBehaviour
{
    // Start is called before the first frame update

    public Renderer rend;
    public GameObject SideLine;

    public Color myColor;
    public float rFloat;
    public float gFloat;
    public float bFloat;

    public GameObject prValue;

    public TMP_Text prText;

    int psrVal;

    bool init = true;

    string pVal;

    // [SerializeField] public Color newColor;
    // [SerializeField] public Color[] colors;

    //private int colorValue;

    public TextMeshProUGUI textComponent;
     // KartGame.KartSystems.KeyboardInput ki = new KartGame.KartSystems.KeyboardInput();
       // psrVal = int.Parse(ki.prs);   
   KartGame.KartSystems.KeyboardInput  keyboardInput;
   
    void Start()
    {
       
     
       // prValue = GameObject.Find("PressureValue");
       //pVal = ki.PressureValue.text;
       //pVal = prText.text;
       //Debug.Log("****this pVal: "+pVal);
        keyboardInput = KartGame.KartSystems.KeyboardInput.Instance;
     
        rend = SideLine.GetComponentInChildren<Renderer>();
           
    }

    // Update is called once per frame
    void Update()
    {
         pVal = prText.text;
         psrVal = int.Parse(pVal);

           //psrVal = int.Parse(keyboardInput.prs);
        
        if((psrVal == 0) && (init == true)){ // init for establishing an initial color (green) to return to.
           
           gFloat=1.00f;
           bFloat=0;
           rFloat=0;
          //  Debug.Log("newPrs: "+ psrVal);
        }
        
        if(psrVal > 50){
            init = false;
            if (bFloat < 1)
            {
                bFloat += 0.01f;
                 gFloat -= 0.01f;
            }
           // else { bFloat = 0; }
          //  Debug.Log("newPrs: "+ psrVal);
        }
         else if (psrVal <= 50)
        {
            if (gFloat < 1)
            {
                bFloat -= 0.01f;
                gFloat += 0.01f;
                rFloat = 0;
            }
            else if((gFloat == 1)&&(bFloat==0)){
                init = true;
            }
            //else { gFloat = 0; }
        }
       
/*
        if (Input.GetKey(KeyCode.R))
        {
            if (rFloat < 1)
            {
                rFloat += 0.01f;
            }
            else { rFloat = 0; }
        }

        if (Input.GetKey(KeyCode.G))
        {
            if (gFloat < 1)
            {
                gFloat += 0.01f;
            }
            else { gFloat = 0; }
        }

        if (Input.GetKey(KeyCode.B))
        {
            if (bFloat < 1)
            {
                bFloat += 0.01f;
            }
            else { bFloat = 0; }
        }
*/ 
        myColor = new Color(rFloat, gFloat, bFloat);
        rend.material.color = myColor;
    }

 GUIStyle guiStyle = new GUIStyle();
        void OnGUI(){
            guiStyle.fontSize = 30;
            string newString = "new pVal: " + pVal;
           //  string prString = "PressureValue: " + prs;
            GUI.Label(new Rect(300,200,100,100), newString, guiStyle);
            // GUI.Label(new Rect(700,250,100,100), prString, guiStyle);
        }


    /*
    public void ChangeMaterial()
    {

        rend.material.color = newColor;
    }
    */
}
