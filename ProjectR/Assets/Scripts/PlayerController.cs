using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Vector3 movement;
    private float horizontalMove = 0.0f;
    private float verticalMove = 0.0f;

    // 이동 속도 변수
    public float moveSpeed = 2.0f;
    public float rotateSpeed = 20.0f;
    // 점프 속도 변수
    public float jumpSpeed = 5.0f;

    private bool bIsJump = false;

    private Rigidbody rigidbody;
    private Animator animator;

    // 최초로 로딩될 때 단 한번 실행됩니다.
    void Awake()
    {
        rigidbody = GetComponent<Rigidbody>();
        animator = GetComponent<Animator>();
    }

    // Update 사이클 진입 전 실행됩니다.
    void Start()
    {
    }

    // 하나의 프레임마다 실행합니다. 최대 1초당 60프레임까지 실행됩니다.
    void Update()
    {
        horizontalMove = Input.GetAxis("Horizontal");
        verticalMove = Input.GetAxis("Vertical");

        if (Input.GetButtonDown("Jump"))
        {
            bIsJump = true;
        }

        AnimationUpdate();
    }

    // 하나의 고정 프레임마다 실행, 물리, 리즈드바디에 대한 로직을 둡니다.
    void FixedUpdate()
    {
        Move();
        Turn();
        Jump();
    }

    void Move()
    {
        movement.Set(horizontalMove, 0, verticalMove);
        movement = movement.normalized * moveSpeed * Time.deltaTime;

        rigidbody.MovePosition(transform.position + movement);
    }

    void Turn()
    {
        if(horizontalMove == 0 && verticalMove == 0)
        {
            return;
        }

        Quaternion newRotation = Quaternion.LookRotation(movement);

        rigidbody.rotation = Quaternion.Slerp(rigidbody.rotation, newRotation, rotateSpeed * Time.deltaTime);
    }

    void Jump()
    {
        if (!bIsJump)
        {
            return;
        }

        // ForceMode.Impulse : 리지드바디의 질량을 사용해서, 짧은 순간의 힘을 가합니다.
        rigidbody.AddForce(Vector3.up * jumpSpeed, ForceMode.Impulse);

        bIsJump = false;
    }

    void AnimationUpdate()
    {
        if(horizontalMove == 0 && verticalMove == 0)
        {
            animator.SetBool("bIsWalk", false);
        }
        else
        {
            animator.SetBool("bIsWalk", true);
        }
    }
}
