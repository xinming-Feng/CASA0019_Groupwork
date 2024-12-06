using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;


public class RingChartUpdater : MonoBehaviour
{
    public RingChart RingChartData;
    void Start()
    {
        RingChartData = GetComponent<RingChart>();
        
    }

    void Update()
    {
        // RingChartData.UpdateData("serie0",0,value);
    }

    public void UpdateRing(List<double> value){

        RingChartData.UpdateData("serie0",0,value);
        



    }
}
