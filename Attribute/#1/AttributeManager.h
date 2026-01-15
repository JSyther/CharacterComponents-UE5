#pragma region Attribute

public:
	/*General*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetCurrentAttributeValueByType(ECharacterAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMinimumAttributeValueByType(ECharacterAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMaximumAttributeValueByType(ECharacterAttributeType AttributeType);

	/*Primary Attribute*/

	/*
	* Accessor
	*/

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FAttributeModule GetPrimaryAttributeModuleByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeMinimumValueByType(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetPrimaryAttributeMaximumValueByType(EPrimaryAttributeType AttributeType);

	/*
	* Mutator
	*/

	/*Secondary Attribute*/

	/*
	* Accessor
	*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	FAttributeModule GetSecondaryAttributeModuleByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeCurrentValueByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeMinimumValueByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetSecondaryAttributeMaximumByType(ESecondaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	float GetMaximumAttributeByType(ECharacterAttributeType AttributeType);

	/*
	* Mutator
	*/
	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetPrimaryAttributeValueByType(EPrimaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	void SetSecondaryAttributeValueByType(ESecondaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool HasPrimaryAttributeValue(EPrimaryAttributeType AttributeType);

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool HasSecondaryAttributeValue(ESecondaryAttributeType AttributeType);

#pragma endregion
