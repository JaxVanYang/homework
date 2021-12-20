package com.example.demo.entity;

import lombok.Data;

@Data
public class Fish {
    private String fishId;
    private String fishName;
    private String fishFamily;

    public void setFishId(String fishId) {
        this.fishId = fishId;
    }

    public void setFishName(String fishName) {
        this.fishName = fishName;
    }

    public void setFishFamily(String fishFamily) {
        this.fishFamily = fishFamily;
    }

    public String getFishId() {
        return fishId;
    }

    public String getFishName() {
        return fishName;
    }

    public String getFishFamily() {
        return fishFamily;
    }
}