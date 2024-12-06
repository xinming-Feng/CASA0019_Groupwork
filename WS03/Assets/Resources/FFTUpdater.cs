using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;

public class FFTUpdater : MonoBehaviour
{
    public BarChart FFT;
    // Start is called before the first frame update
    void Start()
    {
        FFT = GetComponent<BarChart>();
        
        
    }

    public void UpdateChart(float[] values){
        FFT.RemoveData();
        var serie = Bar.AddDefaultSerie(FFT,"FFT");
        for (int i = 0; i<values.Length; i++){
            FFT.AddData(serie.index,values[i]);
            Debug.Log($"dkkkxcx:{values[i]}");
        }
        FFT.RefreshChart();


    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
