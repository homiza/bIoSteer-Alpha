using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using TMPro;

namespace KartGame.KartSystems {

    public class KeyboardInput : BaseInput
    {
        public string TurnInputName = "Horizontal";
        public string AccelerateButtonName = "Accelerate";
        public string BrakeButtonName = "Brake";
        
        public float speed = 5;
        public float rotateSpeed = 90;

        public float rotateAmount;
        
        int steerState;
        public string prs;

        string [] value;

        string recMsg, e;
        public TMP_Text PressureValue, PulseValue;

        public static KeyboardInput Instance;

        void Awake(){
            Instance = this;
        }

        void start(){
            //stream.Open();

        }
        void OnMessageArrived(string msg)
    {
    
        
        // Debug.Log("Arrived: " + msg);
         

        recMsg = msg;

          //  int x = int.Parse(elements[0]);
           /*
            PressureValue.text = elements[0];
            SteeringValue.text = elements[1];
            PulseValue.text = elements[3];
          */
          
    }


     void Update()
    {
        value = recMsg.Split(' ');
        prs = value[0];
        PressureValue.text = value[0];
        //steerState = int.Parse(value[1]);
        e = value[1];
        PulseValue.text = value[2];
        string b = value[3];
        
       

    }
    InputData ida = new InputData();



    void FixedUpdate(){
         
      //  PressureValue.text = prs;
 

          ida.TurnInput = Input.GetAxis("Horizontal") * Time.deltaTime * speed;
	            transform.Rotate(Vector3.up * ida.TurnInput);
                rotateAmount = rotateSpeed * Time.deltaTime;

                if (e == "1"){
                transform.Rotate(0, rotateAmount, 0);
                     Debug.Log("turn right");

                }
                 if (e == "-1"){
                transform.Rotate(0, -rotateAmount, 0);
                      Debug.Log("turn left");

                }
                 if (e == "0"){
                     transform.Rotate(0, rotateAmount*0, 0);
                      Debug.Log("forward");
                }


              if (Input.GetKey(KeyCode.Y)){
                transform.Rotate(0, -rotateAmount, 0);
                      Debug.Log(" Y Button pressed!!");

                }
                // Debug.Log("recieved: " + steerState);
    } 

      GUIStyle guiStyle = new GUIStyle();
        void OnGUI(){
            guiStyle.fontSize = 30;
            string newString = "SteerState: " + e;
            string pString = "pulse: " + PulseValue.text;
           //  string prString = "PressureValue: " + prs;
            GUI.Label(new Rect(700,200,100,100), newString, guiStyle);
            GUI.Label(new Rect(700,600,100,100), pString, guiStyle);
        }

    // Invoked when a connect/disconnect event occurs. The parameter 'success'
    // will be 'true' upon connection, and 'false' upon disconnection or
    // failure to connect.
    void OnConnectionEvent(bool success)
    {
        Debug.Log(success ? "Device connected" : "Device disconnected");
    }

        public override InputData GenerateInput() {
            return new InputData
            {
                Accelerate = Input.GetButton(AccelerateButtonName),
                Brake = Input.GetButton(BrakeButtonName),
             
                TurnInput = Input.GetAxis("Horizontal") // GetAxis is Unity defualt "A & D or Arrow L R keys". SOOOOOO..I need to write a new GetAxis or modify this
                
            };
        }

      
    }
}
