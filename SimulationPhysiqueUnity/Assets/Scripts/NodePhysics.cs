using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.Experimental.GraphView;
using UnityEngine;

public class NodePhysics : MonoBehaviour
{
    [SerializeField] 
    private List<GameObject> links = new();
    
    [SerializeField]
    private float _mass = 1.0f;

    private Vector2 _F_g;
    private Vector2 _F_d;
    private Vector3 _a;
    private Vector3 _v;
    private float coef = 0.315f;

    private Vector3 lastP;
    
    void Start()
    {
        _F_g = _mass * new Vector3(0, -9.81f, 0);
        _v = Vector3.zero;
        _F_d = -coef * norm(_v) * _v;
        lastP = transform.position;
        
        Vector2 f_links = new();
        foreach (GameObject link in links)
        {
            f_links += link.GetComponent<LinkManager>().GetForce(transform);
        }
        _F_d = -coef * norm(_v) * _v;
        _a = (_F_g + f_links + _F_d) / _mass;
        _v = _v + Time.fixedDeltaTime * _a;
        
        transform.position = lastP + Time.fixedDeltaTime * _v;
    }

    private float norm(Vector2 v)
    {
        return Mathf.Sqrt(v.x * v.x + v.y * v.y);
    }

    private void FixedUpdate()
    {
        Vector2 f_links = new();
        foreach (GameObject link in links)
        {
            f_links += link.GetComponent<LinkManager>().GetForce(transform);
        }
        _F_d = -coef * norm(_v) * _v;
        _a = (_F_g + f_links + _F_d) / _mass;
        
        
        (lastP, transform.position) = (transform.position, 2 * transform.position - lastP + (Time.fixedDeltaTime * Time.fixedDeltaTime) * _a);
        _v = (transform.position - lastP) / Time.fixedDeltaTime;
    }
}
