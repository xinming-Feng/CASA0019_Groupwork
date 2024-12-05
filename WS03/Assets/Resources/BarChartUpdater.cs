using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;

public class BarChartUpdater : MonoBehaviour
{
    public BarChart db;
    // Start is called before the first frame update
    void Start()
    {
        db = GetComponent<BarChart>();
        
        
    }

    public void UpdateChart(double value){
        db.RemoveData();
        var serie = Bar.AddDefaultSerie(db,"db");
        db.AddData(serie.index,value);
        db.RefreshChart();



    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
