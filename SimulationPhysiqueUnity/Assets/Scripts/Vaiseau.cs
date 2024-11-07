using System.Collections.Generic;
using UnityEngine;

public class Vaiseau : MonoBehaviour
{
    [SerializeField] 
    private float propulsion;
    [SerializeField] 
    private float mass = 1;
    [SerializeField]
    private float angularSpeed;
    [SerializeField] 
    private float inertia;
    
    [SerializeField] 
    private GameObject directionObject;
    
    [SerializeField] 
    private List<Propulseur> propulseur;
    
    private Vector3 _a;
    private Vector3 _aw;
    private Vector3 _v;
    private Vector3 _vw;
    private Vector3 _pw;
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
        
        _aw = Vector3.zero;
        _pw = Vector3.zero;
        _vw = Vector3.zero;
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

        Vector3 F_p = (D_propulsion * propulsion);
        
        _a = Vector3.zero;
        _aw = Vector3.zero;
        Vector3 l;
        if (Input.GetKey(propulseur[0].propulseurKey))
        {
            _a += F_p;
            l = transform.position - propulseur[0].propulseurGO.transform.position;
            _aw += Vector3.forward * Vector3.Dot(Vector3.Cross(l, F_p), new(0,0,1));
        }

        if (Input.GetKey(propulseur[1].propulseurKey))
        {
            _a += F_p;
            l = transform.position - propulseur[1].propulseurGO.transform.position;
            _aw += Vector3.forward * Vector3.Dot(Vector3.Cross(l, F_p), new(0,0,1));
        }

        _a /= mass;
        _aw /= inertia;

        _v = _a * Time.fixedDeltaTime;
        
        transform.position += _v * Time.fixedDeltaTime;
        directionObject.transform.position += _v * Time.fixedDeltaTime;
        for (int i = 0; i < propulseur.Count; i++)
        {
            propulseur[i].propulseurGO.transform.position += _v * Time.fixedDeltaTime;
        }
        
        _vw = _aw * angularSpeed * Time.fixedDeltaTime;
        _pw = _vw * Time.fixedDeltaTime;
        
        transform.RotateAround(transform.position, Vector3.forward, _pw.z);
        directionObject.transform.RotateAround(transform.position, Vector3.forward, _pw.z);
        for (int i = 0; i < propulseur.Count; i++)
        {
            propulseur[i].propulseurGO.transform.RotateAround(transform.position, Vector3.forward, _pw.z);
        }
        
    }
}
