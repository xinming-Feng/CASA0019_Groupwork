using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using XCharts.Runtime;

public class LineChartUpdater : MonoBehaviour
{
    public LineChart timeDomain;
    // Start is called before the first frame update
    void Start()
    {
        timeDomain = GetComponent<LineChart>();


        
    }

    public void UpdateData(int[] values) {
        var serie = Line.AddDefaultSerie(timeDomain,"Time Domain");
        for (int i = 0; i<values.Length; i++){
            timeDomain.AddData(serie.index,values[i]);
        }
        timeDomain.RefreshChart();

    }
    
    // Update is called once per frame
    void Update()
    {
        
    }
}
