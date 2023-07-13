using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ControlParticle : MonoBehaviour
{
    // Listen to change in thrust
    // adjust Particle values

    // max particles at 500..so pulse to control max particles

    [SerializeField]
    private ParticleSystem sys;

    [SerializeField]
    private float minStartSpeed, maxStartSpeed;
    float speed;
    //Create a subsystem which includes the ones you modify (emission etc) in particlesystem 
    private ParticleSystem.MainModule sysMain;

    
    private void OnEnable()
    {
        sysMain = sys.main;
    }

     void update() // trying to control minspeed of particles with key input
    {
         if (Input.GetKey(KeyCode.K))
         {
            if (minStartSpeed < 1)
            {
                minStartSpeed = 10;
            }

            else {minStartSpeed = 0;}
    
         }

         

    }


    private void SetStartSpeed(float thrustInPercent)
    {

        sysMain.startSpeed = speed;
    }

   
}