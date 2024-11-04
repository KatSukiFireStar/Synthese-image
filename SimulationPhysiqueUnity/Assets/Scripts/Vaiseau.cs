using System.Collections.Generic;
using UnityEngine;

public class Vaiseau : MonoBehaviour
{
    [SerializeField] 
    private float propulsion;
    [SerializeField] 
    private float mass = 1;
    
    [SerializeField] 
    private GameObject directionObject;
    
    [SerializeField] 
    private List<Propulseur> propulseur;
    
    private Vector3 _a;
    private Vector3 _v;
    private List<Vector3> lastP = new();
    private List<Vector3> defaultPosition = new();
    private Vector3 D_propulsion => (directionObject.transform.position - transform.position).normalized;
    
    void Start()
    {
        defaultPosition.Add(transform.position);
        defaultPosition.Add(directionObject.transform.position);
        foreach (Propulseur prop in propulseur)
        {
            defaultPosition.Add(prop.propulseurGO.transform.position);
        }
        
        _v = Vector3.zero;
        lastP.Add(transform.position);
        lastP.Add(directionObject.transform.position);

        foreach (Propulseur prop in propulseur)
        {
            lastP.Add(prop.propulseurGO.transform.position);
        }
        
        _a = Vector3.zero;
        if (Input.GetKey(propulseur[0].propulseurKey))
        {
            _a += (D_propulsion * propulsion);
        }

        if (Input.GetKey(propulseur[1].propulseurKey))
        {
            _a += (D_propulsion * propulsion);
        }

        _a /= mass;
        _v = _v + Time.fixedDeltaTime * _a;
        
        transform.position = lastP[0] + Time.fixedDeltaTime * _v;
        directionObject.transform.position = lastP[1] + Time.fixedDeltaTime * _v;

        for (int i = 0; i < propulseur.Count; i++)
        {
            propulseur[i].propulseurGO.transform.position = lastP[i + 2] + Time.fixedDeltaTime * _v;
        }
    }

    private void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.Space))
        {
            transform.position = defaultPosition[0];
            directionObject.transform.position = defaultPosition[1];
            
            for (int i = 0; i < propulseur.Count; i++)
            {
                propulseur[i].propulseurGO.transform.position = defaultPosition[i + 2];
            }
        }
        
        
        _a = Vector3.zero;
        if (Input.GetKey(propulseur[0].propulseurKey))
        {
            _a += (D_propulsion * propulsion);
        }

        if (Input.GetKey(propulseur[1].propulseurKey))
        {
            _a += (D_propulsion * propulsion);
        }

        _a /= mass;
        
        (lastP[0], transform.position) = (transform.position, 2 * transform.position - lastP[0] + (Time.fixedDeltaTime * Time.fixedDeltaTime) * _a);
        (lastP[1], directionObject.transform.position) = (directionObject.transform.position, 2 * directionObject.transform.position - lastP[1] + (Time.fixedDeltaTime * Time.fixedDeltaTime) * _a);

        for (int i = 0; i < propulseur.Count; i++)
        {
            (lastP[i + 2], propulseur[i].propulseurGO.transform.position) = (propulseur[i].propulseurGO.transform.position, 2 * propulseur[i].propulseurGO.transform.position - lastP[i + 2] + (Time.fixedDeltaTime * Time.fixedDeltaTime) * _a);
        }
    }
}
