#ifndef KUBOT_MODEL_H_
#define KUBOT_MODEL_H_

// 運動學模型樣板
struct Model {
    // 構造函數
    Model() {}
    Model(float _wheel_radius, float _body_radius) : wheel_radius(_wheel_radius), body_radius(_body_radius) {}
    Model(float _wheel_radius, float _body_radius, float _stick_radius) : wheel_radius(_wheel_radius), body_radius(_body_radius), stick_radius(_stick_radius) {}

    // 用於參數更新
    void set(float _wheel_radius, float _body_radius) {
        wheel_radius = _wheel_radius;
        body_radius = _body_radius;
    }

    void set(float _wheel_radius, float _body_radius, float _stick_radius) {
        wheel_radius = _wheel_radius;
        body_radius = _body_radius;
        stick_radius = _stick_radius;
    }

    ~Model() {}

    // robot speed ---> motor speed 
    // 運動解算, 把給機器人的速度換算成各個輪子的速度
    virtual void motion_solver(float* robot_speed, float* motor_speed) = 0;

    // motor speed ---> robot speed 
    // 運動反解算, 把各個輪子的速度轉為機器人速度 (以固定時間更新的里程計計算)
    virtual void get_odom(struct Odom* odom, float* motor_dis, unsigned long interval) = 0;

protected:
    float wheel_radius; // 輪子半徑
    float body_radius;  // 輪距(或其他係數)
    float stick_radius; // 旋轉半徑(或其他係數)
};

// 里程計訊息
struct Odom {
    float x;
    float y;
    float z;
    float vel_x;
    float vel_y;
    float vel_z;
};

#endif